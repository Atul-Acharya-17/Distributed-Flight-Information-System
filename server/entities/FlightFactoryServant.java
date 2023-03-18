package entities;
import java.io.File;
import java.util.ArrayList;
import java.util.Hashtable;
import java.util.Iterator;
import java.util.Map;
import java.util.Scanner;

public class FlightFactoryServant implements FlightFactory {
    private static Hashtable<String, Flight> flights = new Hashtable<>();
    public FlightFactoryServant() {
        super();
    }

    public void createFlight(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price) {
        Flight flight = new FlightServant(flightID.toCharArray(), source.toCharArray(), destination.toCharArray(), seatsAvailable, seatsBooked, price);
        flights.put(flightID, flight);
    }

    public void bookSeat(String flightID) {
        Flight flight = flights.get(flightID);
        flight.setSeatsAvailable(flight.getSeatsAvailable() - 1);
        flight.setSeatsBooked(flight.getSeatsBooked() + 1);
    }

    public boolean checkFlight(String flightID)
    {
        this.displayFlights();
        return flights.containsKey(flightID);
    }

    public Flight getFlight(String flightID)
    {
        return flights.get(flightID);
    }

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

    public void sendNotification(String clientID) {
        //TODO: Which class is storing the clientID?
        
        // ClientCallback client = ClientCallbackFactory.getClientCallback(clientID);
        // client.notifyClient();
    }

    public void registerClientCallback(String clientID) {
        // ClientCallback client = ClientCallbackFactory.getClientCallback(clientID);
        // client.registerClientCallback();
    }

    public void unregisterClientCallback(String clientID) {
        // ClientCallback client = ClientCallbackFactory.getClientCallback(clientID);
        // client.unregisterClientCallback();
    }

    public void displayFlights() {
        Iterator<Map.Entry<String,Flight>> itr = flights.entrySet().iterator();
        Map.Entry<String, Flight> entry = null;
        while(itr.hasNext()) {
            entry = itr.next();
            System.out.println( entry.getKey() + "--->"); 
            entry.getValue().display();
        }
        System.out.println("\n" + flights.size());
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
                createFlight(flightDetails[0], flightDetails[1], flightDetails[2], Integer.parseInt(flightDetails[3]), Integer.parseInt(flightDetails[4]), Float.parseFloat(flightDetails[5]));
            }
            scanner.close();
        }
        catch(Exception e)
        {
            System.out.println(e);
        }        
    }
}
    