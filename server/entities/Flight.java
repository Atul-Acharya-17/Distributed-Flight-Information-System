package entities;
import java.time.LocalTime;

import marshall.Serialization;

/* 
    Interface for a Flight object containing information related to a flight.
    Inherits from Serializable which allows to serialize objects.
*/
public interface Flight extends Serialization {

    public char[] getFlightId();
    public void setFlightId(char[] flightId);

    public char[] getSource();
    public void setSource(char[] source);

    public char[] getDestination();
    public void setDestination(char[] destination);

    public int getSeatsAvailable();
    public void setSeatsAvailable(int seatsAvailable);

    public int getSeatsBooked();
    public void setSeatsBooked(int seatsBooked);
    
    public float getPrice(); //Price per seat
    public void setPrice(float price);

    public LocalTime getDepartureTime();
    public LocalTime getDuration();

    public void display();

}