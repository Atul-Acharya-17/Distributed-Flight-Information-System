package skeleton;

import java.io.IOException;
import communication.Reply;
import entities.FlightFactoryServant;
import entities.FlightServant;
import marshall.SerializePOD;


/*
    Skeleton to handle querying flight number.
    Sends the client the flight details given the flight number.
*/

public class FlightQuerySkeleton extends Skeleton {

    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        // Check for duplicate request
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) return;
        
        // Unmarshall Reply contents
        char[] flightID = SerializePOD.deserializeString(content, 0);
        FlightFactoryServant fm = new FlightFactoryServant();
        FlightServant fs = (FlightServant) fm.getFlight(new String(flightID));

        short status = 0;
        byte[] replyContent;

        // Return error if no such flight exists
        if (fs == null)
        {
            status = 1;
            replyContent = SerializePOD.serialize("Flight number does not exist".toCharArray());
        }

        else {
            // Unmarshall reply contents
            replyContent = fs.serialize();
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);
        
        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
