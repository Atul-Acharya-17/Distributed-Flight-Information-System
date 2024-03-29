package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.Booking;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;


/*
    Skeleton to handle cancellation of reservation of seats in a flight.
*/

public class CancelReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        short status = 0;
        byte[] replyContent;

        // Check for duplicate request
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) {
            return;
        }
        
        // Unmarshall reply contents
        int idx = 0;
        String booking_id = new String(SerializePOD.deserializeString(content, idx));
        idx += booking_id.length() + PrimitiveSizes.sizeof((long) booking_id.length());

        // Cancel booking
        BookingFactoryServant fm = new BookingFactoryServant();
        if (fm.checkBookingExists(booking_id))
        {
            //Cancel booking
            Booking booking = fm.getBooking(booking_id);
            String flight_id = new String(booking.getFlightId());
            boolean result = fm.cancelBooking(booking_id);

            //Publish cancellation to subscribers
            String rep = "Booking " + booking_id + " cancelled succesfully";
            replyContent = SerializePOD.serialize(rep.toCharArray());
            FlightPublisherSkeleton.publish(flight_id);
        }
        
        // Send error message if no booking found
        else
        {
            status = 1;
            replyContent = SerializePOD.serialize("Booking not found".toCharArray());
        }
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);

        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
