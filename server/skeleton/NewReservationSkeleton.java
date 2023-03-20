package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.Booking;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class NewReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, char[] clientIP, int port, int requestId) throws IOException
    {
        int idx = 0;
        String flight_id = new String(SerializePOD.deserializeString(content, idx));
        idx += flight_id.length() + PrimitiveSizes.sizeof((long) flight_id.length());
        String customer_name = new String(SerializePOD.deserializeString(content, idx));
        idx += customer_name.length() + PrimitiveSizes.sizeof((long) customer_name.length());
        int num_seats = SerializePOD.deserializeInt(content, idx);

        BookingFactoryServant fm = new BookingFactoryServant();
        Booking result = fm.createBooking(flight_id, customer_name, num_seats);

        short status = 0;
        byte[] replyContent;

        if (result==null)
        {
            status = 1;
            String rep = num_seats + " seats unavailable on selected flight";
            replyContent = SerializePOD.serialize(rep.toCharArray());
        }
        
        else {
            replyContent = result.serialize(); 
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        communication.Communication.send(new String(clientIP), port, replyBuffer);
    }
}
