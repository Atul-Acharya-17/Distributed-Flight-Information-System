package skeleton;

import java.io.IOException;
import java.util.ArrayList;
import communication.Reply;
import entities.FlightFactoryServant;
import entities.TripServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class TripPlanSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) {
            return;
        }

        int idx = 0;
        String source = new String(SerializePOD.deserializeString(content, idx));
        idx += source.length() + PrimitiveSizes.sizeof((long) source.length());
        String destination = new String(SerializePOD.deserializeString(content, idx));
        idx += destination.length() + PrimitiveSizes.sizeof((long) destination.length());

        // int numFlights = SerializePOD.deserializeInt(content, idx);
        // idx += PrimitiveSizes.sizeof(numFlights);

        // float maxCost = SerializePOD.deserializeFloat(content, idx);
        // idx += PrimitiveSizes.sizeof(maxCost);

        FlightFactoryServant fm = new FlightFactoryServant();
        ArrayList<TripServant> result = fm.planTrip(source, destination, 2, Float.MAX_VALUE);

        short status = 0;
        byte[] replyContent;

        if (result.size() == 0)
        {
            status = 1;
            replyContent = SerializePOD.serialize("No flights found".toCharArray());
        }

        else {
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
