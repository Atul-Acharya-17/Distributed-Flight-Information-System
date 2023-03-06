package server;

import java.rmi.server.UnicastRemoteObject;

public class FlightServant extends UnicastRemoteObject implements Flight {
    private String flightID;
    private String source;
    private String destination;
    private int seatsAvailable;
    private int seatsBooked;
    private float price;

    public FlightServant(String flightID, String source, String destination, int seatsAvailable, int seatsBooked, float price) throws java.rmi.RemoteException {
        super();
        this.flightID = flightID;
        this.source = source;
        this.destination = destination;
        this.seatsAvailable = seatsAvailable;
        this.seatsBooked = seatsBooked;
        this.price = price;
    }

    public String getFlightID() throws java.rmi.RemoteException {
        return flightID;
    }

    public void setFlightID(String flightID) throws java.rmi.RemoteException {
        this.flightID = flightID;
    }

    public String getSource() throws java.rmi.RemoteException {
        return source;
    }

    public void setSource(String source) throws java.rmi.RemoteException {
        this.source = source;
    }

    public String getDestination() throws java.rmi.RemoteException {
        return destination;
    }

    public void setDestination(String destination) throws java.rmi.RemoteException {
        this.destination = destination;
    }

    public int getSeatsAvailable() throws java.rmi.RemoteException {
        return seatsAvailable;
    }

    public void setSeatsAvailable(int seatsAvailable) throws java.rmi.RemoteException {
        this.seatsAvailable = seatsAvailable;
    }

    public int getSeatsBooked() throws java.rmi.RemoteException {
        return seatsBooked;
    }

    public void setSeatsBooked(int seatsBooked) throws java.rmi.RemoteException {
        this.seatsBooked = seatsBooked;
    }

    public float getPrice() throws java.rmi.RemoteException {
        return price;
    }

    public void setPrice(float price) throws java.rmi.RemoteException {
        this.price = price;
    }
}

