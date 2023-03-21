package entities;

import java.io.IOException;
import java.time.LocalTime;
import java.util.ArrayList;
import java.util.LinkedHashSet;

import entities.Trip;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class TripServant implements Trip, Comparable<TripServant> {
    private ArrayList<String> flights;
    private float price;
    private int numFlights;
    private ArrayList<LocalTime> departureTimes;
    private ArrayList<String> cities;
    private ArrayList<LocalTime> durations;

    public TripServant() {}

    @Override
    public long size() {
        long size = PrimitiveSizes.sizeof(numFlights) + PrimitiveSizes.sizeof(this.price);

        for (String flight : this.flights) {
            size += flight.length() + PrimitiveSizes.sizeof((long) flight.length());
        }

        for (String city : this.cities) {
            size += city.length() + PrimitiveSizes.sizeof((long) city.length());
        }

        for (LocalTime time : this.departureTimes) {
            size += PrimitiveSizes.sizeof(time.toSecondOfDay());
        }

        for (LocalTime time : this.durations) {
            size += PrimitiveSizes.sizeof(time.toSecondOfDay());
        }

        return size;
    }

    public TripServant(ArrayList<String> flights, LinkedHashSet<String> cities, float price, ArrayList<LocalTime>departureTimes, ArrayList<LocalTime>durations)
    {
        this.flights = flights;
        this.price = price;
        this.numFlights = this.flights.size();
        this.departureTimes = departureTimes;
        this.cities = new ArrayList<>();
        this.cities.addAll(cities);
        this.durations = durations;
    }

    @Override
    public void deserialize(byte[] dataIn) {
        int start = 0;
        
        int numFlights = SerializePOD.deserializeInt(dataIn, start);
        start += PrimitiveSizes.sizeof(numFlights);

        this.flights.clear();

        for (int i=0; i<numFlights; ++i)
        {
            char[] flightID = SerializePOD.deserializeString(dataIn, start);
            this.flights.add(new String(flightID));
            start += flightID.length + PrimitiveSizes.sizeof((long) flightID.length);
        }

        for (int i=0; i<numFlights+1; ++i)
        {
            char[] city = SerializePOD.deserializeString(dataIn, start);
            this.cities.add(new String(city));
            start += city.length + PrimitiveSizes.sizeof((long) city.length);
        }

        for (int i=0; i<numFlights+1; ++i)
        {
            int depTimeInSeconds = SerializePOD.deserializeInt(dataIn, start);
            this.departureTimes.add(LocalTime.ofSecondOfDay(depTimeInSeconds));
            start += PrimitiveSizes.sizeof(depTimeInSeconds);
        }

        for (int i=0; i<numFlights; ++i)
        {
            int durationInSeconds = SerializePOD.deserializeInt(dataIn, start);
            this.durations.add(LocalTime.ofSecondOfDay(durationInSeconds));
            start += PrimitiveSizes.sizeof(durationInSeconds);
        }

        this.price = SerializePOD.deserializeFloat(dataIn, start);
        start += PrimitiveSizes.sizeof(price);
    }

    @Override
    public byte[] serialize() throws IOException {
        byte[] buffer = new byte[(int)this.size()];

        byte[] numFlightsBuffer = SerializePOD.serialize(this.flights.size());

        int i = 0;
        System.arraycopy(numFlightsBuffer, 0, buffer, i, numFlightsBuffer.length);
        i += numFlightsBuffer.length;

        for (String flight : flights) {
            byte[] flightBuffer = SerializePOD.serialize(flight);
            System.arraycopy(flightBuffer, 0, buffer, i, flightBuffer.length);
            i += flightBuffer.length;
        }

        for (String city : this.cities) {
            byte[] cityBuffer = SerializePOD.serialize(city);
            System.arraycopy(cityBuffer, 0, buffer, i, cityBuffer.length);
            i += cityBuffer.length;
        }

        for (LocalTime time : this.departureTimes) {
            byte[] depTimeBuffer = SerializePOD.serialize(time.toSecondOfDay());
            System.arraycopy(depTimeBuffer, 0, buffer, i, depTimeBuffer.length);
            i += depTimeBuffer.length;
        }

        for (LocalTime time : this.durations) {
            byte[] durationBuffer = SerializePOD.serialize(time.toSecondOfDay());
            System.arraycopy(durationBuffer, 0, buffer, i, durationBuffer.length);
            i += durationBuffer.length;
        }

        byte[] priceBuffer = SerializePOD.serialize(price);

        System.arraycopy(priceBuffer, 0, buffer, i, priceBuffer.length);

        return buffer;
    }

    @Override
    public ArrayList<String> getFlights() {
        return this.flights;
    }

    @Override
    public void setFlights(ArrayList<String> flights) {
        this.flights = flights;
    }

    @Override
    public float getPrice() {
        return this.price;
    }

    @Override
    public void setPrice(float price) {
        this.price = price;
    }

    @Override
    public void display() {
        System.out.print("Flights: ");

        System.out.print(this.cities.get(0));

        for (int i=0; i<this.flights.size(); ++i)
        {
            System.out.print("(" + this.departureTimes.get(i) + ")");
            System.out.print(" --- " + this.flights.get(i) + "(" + this.durations.get(i) + ") " +  "--> " + this.cities.get(i+1));
            if (i==this.flights.size()-1)System.out.print("(" + this.departureTimes.get(i+1) +")");
        }
        System.out.print('\n');
        System.out.println("Price: " + this.price);
    }

    @Override
    public int compareTo(TripServant o) {

        if (this.price < o.price)
        {
            return -1;
        }
        if (this.price > o.price)
        {
            return 1;
        }

        else {
            if (this.flights.size() <= o.flights.size()) return -1;
            return 1;
        }
    }
    
}
