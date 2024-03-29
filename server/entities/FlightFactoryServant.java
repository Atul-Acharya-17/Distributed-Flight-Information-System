package entities;
import java.io.File;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.LinkedHashSet;
import java.util.Map;
import java.util.Scanner;

/*
 * Implementation of Booking Factory interface.
 * Implements functions for reading flights from file, lookup flights based on source-destination or flight ID, 
 * calculating multi-city trips using DFS, and displaying all flights.
 */
public class FlightFactoryServant implements FlightFactory {
    private static Hashtable<String, Flight> flights = new Hashtable<>();
    public FlightFactoryServant() {
        super();
    }

    @Override
    public void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price, LocalTime departureTime, LocalTime duration) {
        Flight flight = new FlightServant(flightID.toCharArray(), source.toCharArray(), destination.toCharArray(), seatsAvailable, seatsBooked, price, departureTime, duration);
        flights.put(flightID, flight);
    }

    @Override
    public boolean bookSeat(String flightID, int numSeatsBooked) {
        Flight flight = this.getFlight(flightID);
        if (flight.getSeatsAvailable() < numSeatsBooked) {
            return false;
        }
        flight.setSeatsAvailable(flight.getSeatsAvailable() - numSeatsBooked);
        flight.setSeatsBooked(flight.getSeatsBooked() + numSeatsBooked);
        PublishFactoryServant.publishBooking(flightID, numSeatsBooked, flight.getSeatsAvailable());
        return true;
    }

    @Override
    public void cancelSeat(String flightID, int numSeatsBooked) {
        Flight flight = this.getFlight(flightID);
        flight.setSeatsAvailable(flight.getSeatsAvailable() + numSeatsBooked);
        flight.setSeatsBooked(flight.getSeatsBooked() - numSeatsBooked);
        PublishFactoryServant.publishCancellation(flightID, numSeatsBooked, flight.getSeatsAvailable());
    }
    
    @Override
    public boolean checkFlight(String flightID)
    {
        return flights.containsKey(flightID);
    }

    @Override
    public Flight getFlight(String flightID)
    {
        return flights.get(flightID);
    }

    @Override
    public ArrayList<String> findFlights(String source, String destination)
    {
        ArrayList<String> result = new ArrayList<String>();
        
        Iterator<Map.Entry<String,Flight>> itr = flights.entrySet().iterator();
        Map.Entry<String, Flight> entry = null;
        while(itr.hasNext()) {
            entry = itr.next();

            if (new String(entry.getValue().getSource()).equals(source) && new String(entry.getValue().getDestination()).equals(destination))
            {
                result.add(entry.getKey());
            }
        }

        return result;
    }

    @Override
    public ArrayList<String> findFlights(String source)
    {
        ArrayList<String> result = new ArrayList<String>();
        
        Iterator<Map.Entry<String,Flight>> itr = flights.entrySet().iterator();
        Map.Entry<String, Flight> entry = null;
        while(itr.hasNext()) {
            entry = itr.next();

            if (new String(entry.getValue().getSource()).equals(source))
            {
                result.add(entry.getKey());
            }
        }

        return result;
    }

    @Override
    public ArrayList<TripServant> planTrip(String source, String destination, int numFlights, float maxCost)
    {
        ArrayList<TripServant> trips = new ArrayList<TripServant>();
        ArrayList<String> flightNums = new ArrayList<>();
        ArrayList<LocalTime> departureTimes = new ArrayList<>();
        ArrayList<LocalTime> durations = new ArrayList<>();
        LinkedHashSet<String> placesVisited = new LinkedHashSet<>();
        placesVisited.add(source);

        LocalTime currentTime = LocalTime.of(0, 0, 0);
        graphSearch(trips, flightNums, placesVisited, departureTimes, durations, currentTime, source, destination, numFlights, 0.0f, maxCost);
        Collections.sort(trips);
        return trips;
    }

    public void graphSearch(ArrayList<TripServant>trips, ArrayList<String> flightNums, LinkedHashSet<String> placesVisited, ArrayList<LocalTime>departureTimes, ArrayList<LocalTime>durations, LocalTime currentTime, String currentLocation, String destination, int flightsRemaining, float spent, float budget)
    {

        if (flightsRemaining < 0) return;

        if (spent > budget) return;

        if (currentLocation.equals(destination))
        {
            departureTimes.add(currentTime);
            TripServant trip = new TripServant((ArrayList)flightNums.clone(), (LinkedHashSet) placesVisited.clone(), spent, (ArrayList) departureTimes.clone(), (ArrayList) durations.clone());
            trips.add(trip);
            departureTimes.remove(currentTime);
            return;
        }

        ArrayList<String> flightIds = findFlights(currentLocation);

        for (String fID : flightIds) {
            Flight flight = getFlight(fID);
            String nextCountry = new String(flight.getDestination());

            if (placesVisited.contains(nextCountry)) continue; // Avoid travelling to same place in same tri

            // if (currentTime.isAfter(departureTime)) continue; // cannot board flight when it has already left
            

            LocalTime departureTime = flight.getDepartureTime();
            LocalTime flightDuration = flight.getDuration();

            placesVisited.add(nextCountry);
            flightNums.add(fID);

            departureTimes.add(departureTime);
            durations.add(flightDuration);

            float cost = flight.getPrice();

            currentTime = departureTime.plusHours(flightDuration.getHour()).plusMinutes(flightDuration.getMinute());

            graphSearch(trips, flightNums, placesVisited, departureTimes, durations, currentTime, nextCountry, destination, flightsRemaining - 1, spent + cost, budget);

            placesVisited.remove(nextCountry);
            flightNums.remove(fID);

            departureTimes.remove(departureTime);
            durations.remove(flightDuration);
        }
    }

    @Override
    public void displayFlights() {
        Iterator<Map.Entry<String,Flight>> itr = flights.entrySet().iterator();
        Map.Entry<String, Flight> entry = null;
        while(itr.hasNext()) {
            entry = itr.next();
            System.out.println( entry.getKey() + "--->"); 
            entry.getValue().display();
        }
    }

    @Override
    public void populateFlights() {
        
        try
        {
            File fileObj = new File(System.getProperty("user.dir") + "/data/flights.txt");
            Scanner scanner = new Scanner(fileObj);
            while(scanner.hasNextLine()){
                String line = scanner.nextLine();
                String[] flightDetails = line.split(",");
                createFlight(flightDetails[0], flightDetails[1], flightDetails[2], Integer.parseInt(flightDetails[3]), Integer.parseInt(flightDetails[4]), Float.parseFloat(flightDetails[5]), LocalTime.parse(flightDetails[6]), LocalTime.parse(flightDetails[7]));
            }
            scanner.close();
        }
        catch(Exception e)
        {
            System.out.println(e);
        }        
    }
}
    