package skeleton;

import java.io.IOException;

import communication.Reply;
import entities.Booking;
import entities.BookingFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class CheckReservationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) {
            return;
        
        int idx = 0;
        String booking_id = new String(SerializePOD.deserializeString(content, idx));
        idx += booking_id.length() + PrimitiveSizes.sizeof((long) booking_id.length());

        BookingFactoryServant fm = new BookingFactoryServant();
        Booking result = fm.getBooking(booking_id);

        short status = 0;
        byte[] replyContent;

        if (result==null)
        {
            status = 1;
            replyContent = SerializePOD.serialize("Booking not found".toCharArray());
        }
        
        else {
            replyContent = result.serialize();
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);
        
        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
