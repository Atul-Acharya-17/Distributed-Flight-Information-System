package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.Booking;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class NewReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) return;
        
        int idx = 0;
        String flight_id = new String(SerializePOD.deserializeString(content, idx));
        idx += flight_id.length() + PrimitiveSizes.sizeof((long) flight_id.length());
        String customer_name = new String(SerializePOD.deserializeString(content, idx));
        idx += customer_name.length() + PrimitiveSizes.sizeof((long) customer_name.length());
        int num_seats = SerializePOD.deserializeInt(content, idx);

        BookingFactoryServant fm = new BookingFactoryServant();
        String result = fm.createBooking(flight_id, customer_name, num_seats);

        short status = 0;
        byte[] replyContent;

        if (result.length() > 6)    // Means an error message, not a booking id
        {
            status = 1;
            replyContent = SerializePOD.serialize(result.toCharArray());
        }
        
        else {
            Booking booking = fm.getBooking(result);
            replyContent = booking.serialize();
            FlightPublisherSkeleton.publish(flight_id);
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);
        
        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
