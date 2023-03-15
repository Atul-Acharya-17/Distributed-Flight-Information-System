

public interface Flight {

    public String getFlightId();
    public void setFlightId(String flightId);

    public String getSource();
    public void setSource(String source);

    public String getDestination();
    public void setDestination(String destination);

    public int getSeatsAvailable();
    public void setSeatsAvailable(int seatsAvailable);

    public int getSeatsBooked();
    public void setSeatsBooked(int seatsBooked);
    
    public float getPrice(); //Price per seat
    public void setPrice(float price);

    public void display();

}