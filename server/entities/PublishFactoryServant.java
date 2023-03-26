package entities;

public class PublishFactoryServant {
    public static PublishServant publish = new PublishServant();

    public PublishFactoryServant()
    {
        super();
    }

    public static void publishCancellation(String FlightID, int numSeatsCancelled, int updatedNumSeats) {
        String msg = numSeatsCancelled + " new seats avail for flight " + FlightID + "\n";
        msg += "Total seats available for flight " + FlightID + " = " + updatedNumSeats + " \n";
        publish.setMsg(msg.toCharArray());
    }

    public static void publishBooking(String FlightID, int numSeatsBooked, int updatedNumSeats) {
        String msg = numSeatsBooked + " seats booked for flight " + FlightID + "\n";
        msg += "Total seats available for flight " + FlightID + " = " + updatedNumSeats + " \n";
        publish.setMsg(msg.toCharArray());
    }

    public static Publish getPublish()
    {
        return publish;
    }

}   
