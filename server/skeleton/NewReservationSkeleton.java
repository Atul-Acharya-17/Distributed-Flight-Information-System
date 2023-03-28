package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.Booking;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;


/*
    Skeleton to handle reservation of seats in a flight.
*/

public class NewReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        // Check for duplicate request
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) return;
        
        // Unmarshall request contents
        int idx = 0;
        String flight_id = new String(SerializePOD.deserializeString(content, idx));
        idx += flight_id.length() + PrimitiveSizes.sizeof((long) flight_id.length());
        String customer_name = new String(SerializePOD.deserializeString(content, idx));
        idx += customer_name.length() + PrimitiveSizes.sizeof((long) customer_name.length());
        int num_seats = SerializePOD.deserializeInt(content, idx);

        // Make booking
        BookingFactoryServant fm = new BookingFactoryServant();
        String result = fm.createBooking(flight_id, customer_name, num_seats);

        short status = 0;
        byte[] replyContent;

        // Return error message if flight number not found or if seats are not available
        // Unique error message is generated for both these errors
        if (result.length() > 6)    // Means an error message, not a booking id
        {
            status = 1;
            replyContent = SerializePOD.serialize(result.toCharArray());
        }
        
        // Marshall reply contents
        else {
            Booking booking = fm.getBooking(result);
            replyContent = booking.serialize(); 
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);
        
        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
