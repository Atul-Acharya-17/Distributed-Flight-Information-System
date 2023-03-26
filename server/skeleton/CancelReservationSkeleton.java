package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.Booking;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class CancelReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        short status = 0;
        byte[] replyContent;
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) {
            return;
        }
        
        int idx = 0;
        String booking_id = new String(SerializePOD.deserializeString(content, idx));
        idx += booking_id.length() + PrimitiveSizes.sizeof((long) booking_id.length());

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
            FlightPublisher.publish(flight_id);
        }
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
