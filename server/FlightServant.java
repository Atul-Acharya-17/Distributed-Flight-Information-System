public class FlightServant implements Flight {
    private String flightId;
    private String source;
    private String destination;
    private int seatsAvailable;
    private int seatsBooked;
    private float price;

    public FlightServant(String flightId, String source, String destination, int seatsAvailable, int seatsBooked, float price) {
        this.flightId = flightId;
        this.source = source;
        this.destination = destination;
        this.seatsAvailable = seatsAvailable;
        this.seatsBooked = seatsBooked;
        this.price = price;
    }

    public String getFlightId() {
        return flightId;
    }

    public void setFlightId(String flightId) {
        this.flightId = flightId;
    }

    public String getSource() {
        return source;
    }

    public void setSource(String source) {
        this.source = source;
    }

    public String getDestination() {
        return destination;
    }

    public void setDestination(String destination) {
        this.destination = destination;
    }

    public int getSeatsAvailable() {
        return seatsAvailable;
    }

    public void setSeatsAvailable(int seatsAvailable) {
        this.seatsAvailable = seatsAvailable;
    }

    public int getSeatsBooked() {
        return seatsBooked;
    }

    public void setSeatsBooked(int seatsBooked) {
        this.seatsBooked = seatsBooked;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    @Override
    public void display() {
        System.out.print(flightId + "@" + source + "->" + destination + "\n");
        System.out.print(seatsAvailable + "-" + seatsBooked + "#" + price + "\n");
    }
}

