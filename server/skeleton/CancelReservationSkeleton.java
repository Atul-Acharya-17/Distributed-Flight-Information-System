package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class CancelReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, char[] clientIP, int port, int requestId) throws IOException
    {
        int idx = 0;
        String booking_id = new String(SerializePOD.deserializeString(content, idx));
        idx += booking_id.length() + PrimitiveSizes.sizeof((long) booking_id.length());

        BookingFactoryServant fm = new BookingFactoryServant();
        boolean result = fm.cancelBooking(booking_id);

        short status = 0;
        byte[] replyContent;

        if (result==false)
        {
            status = 1;
            replyContent = SerializePOD.serialize("Booking not found".toCharArray());
        }
        
        else {
            String rep = "Booking " + booking_id + " cancelled succesfully";
            replyContent = SerializePOD.serialize(rep.toCharArray()); 
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        communication.Communication.send(new String(clientIP), port, replyBuffer);
    }
}
