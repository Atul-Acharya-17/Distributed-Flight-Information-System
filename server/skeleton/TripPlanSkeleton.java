package skeleton;

import java.io.IOException;
import java.util.ArrayList;
import communication.Reply;
import entities.FlightFactoryServant;
import entities.TripServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;


/*
    Skeleton to handle trip plan.
    Sends the client the required flights to take from source to destination.
*/

public class TripPlanSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        // check duplicate request
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) {
            return;
        }

        // Unmarshall Request contents
        int idx = 0;
        String source = new String(SerializePOD.deserializeString(content, idx));
        idx += source.length() + PrimitiveSizes.sizeof((long) source.length());
        String destination = new String(SerializePOD.deserializeString(content, idx));
        idx += destination.length() + PrimitiveSizes.sizeof((long) destination.length());

        // Find available trips
        FlightFactoryServant fm = new FlightFactoryServant();
        ArrayList<TripServant> result = fm.planTrip(source, destination, 3, Float.MAX_VALUE);

        if (result.size() == 0) result = fm.planTrip(source, destination, Integer.MAX_VALUE, Float.MAX_VALUE);

        short status = 0;
        byte[] replyContent;

        // Return error if no trips found
        if (result.size() == 0)
        {
            status = 1;
            replyContent = SerializePOD.serialize("No flights found".toCharArray());
        }

        else {

            // Marshall Trips
            int numResults = result.size();
            int replySize = (int) PrimitiveSizes.sizeof(numResults);

            for (TripServant trip : result) {
                replySize += trip.size();
            }

            replyContent = new byte[replySize];

            int i = 0;

            byte[] numTripsBuffer = SerializePOD.serialize(numResults);

            System.arraycopy(numTripsBuffer, 0, replyContent, i, numTripsBuffer.length);
            i += numTripsBuffer.length;

            for (TripServant tripServant : result) {
                byte[] tripBuffer = tripServant.serialize();
                System.arraycopy(tripBuffer, 0, replyContent, i, tripBuffer.length);
                i += tripBuffer.length;
            }
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);
        
        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
