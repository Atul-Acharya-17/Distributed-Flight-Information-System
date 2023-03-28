package entities;
import java.io.File;
import java.util.Hashtable;
import java.util.Scanner;

public class BookingFactoryServant implements BookingFactory {
    private static Hashtable<String, Booking> bookings = new Hashtable<>();
    public BookingFactoryServant() {
        super();
    }

    @Override
    public String createBooking(String flightId, String clientId, int numSeatsBooked) {
        FlightFactoryServant ffs = new FlightFactoryServant();
        if(!ffs.checkFlight(flightId)) {
            return ("Flight ID " + flightId + " not found");
        }
        Booking booking = new BookingServant(flightId.toCharArray(), clientId.toCharArray(), numSeatsBooked);
        boolean isBooked = ffs.bookSeat(flightId, numSeatsBooked);
        if (isBooked) {
            bookings.put(new String(booking.getBookingId()), booking);
        }
        else {
            int seatsAvailable = ffs.getFlight(flightId).getSeatsAvailable();
            return (numSeatsBooked + " seats cannot be book on flight " + flightId + 
                    ". Only " + seatsAvailable + " are available.");
        }
        return new String(booking.getBookingId());
    }

    @Override
    public void createBookingWithBookingId(String bookingId, String flightId, String clientId, int numSeatsBooked) {
        Booking booking = new BookingServant(bookingId.toCharArray(), flightId.toCharArray(), clientId.toCharArray(), numSeatsBooked);
        FlightFactoryServant ffs = new FlightFactoryServant();
        boolean isBooked = ffs.bookSeat(flightId, numSeatsBooked);
        if (isBooked) {
            bookings.put(new String(booking.getBookingId()), booking);
        }
        else {
            System.out.println("Error in creating booking");
        }
    }

    @Override
    public boolean cancelBooking(String bookingId) {
        if (bookings.containsKey(bookingId)) {
            Booking booking = this.getBooking(bookingId);
            FlightFactoryServant ffs = new FlightFactoryServant();
            ffs.cancelSeat(new String(booking.getFlightId()), booking.getNumSeatsBooked());
            bookings.remove(bookingId);
        }
        else {
            return false;
        }
        return true;
    }

    public Booking getBooking(String bookingId)
    {
        if (bookings.containsKey(bookingId)) {
            return bookings.get(bookingId);
        }
        else {
            return null;
        }
    }

    @Override
    public void populateBookings() {
        try {
            File fileObj = new File(System.getProperty("user.dir") + "/data/bookings.txt");
            Scanner scanner = new Scanner(fileObj);
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine();
                String[] bookingDetails = line.split(",");
                createBookingWithBookingId(bookingDetails[0], bookingDetails[1], bookingDetails[2],
                        Integer.parseInt(bookingDetails[3]));
            }
            scanner.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    
    @Override
    public boolean checkBookingExists(String bookingId)
    {
        if (bookings.containsKey(bookingId)) {
            return true;
        }
        else
            return false;
    }
}    