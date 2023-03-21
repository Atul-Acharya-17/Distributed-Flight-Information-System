package skeleton;

import java.io.IOException;
import java.util.ArrayList;
import communication.Reply;
import entities.FlightFactoryServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class FlightLocationSkeleton extends Skeleton {
    
    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) {
            return;
        
        int idx = 0;
        String source = new String(SerializePOD.deserializeString(content, idx));
        idx += source.length() + PrimitiveSizes.sizeof((long) source.length());
        String destination = new String(SerializePOD.deserializeString(content, idx));

        FlightFactoryServant fm = new FlightFactoryServant();
        ArrayList<String> result = fm.findFlights(source, destination);

        short status = 0;
        byte[] replyContent;

        if (result.size() == 0)
        {
            status = 1;
            replyContent = SerializePOD.serialize("No flights found".toCharArray());
        }

        else{
            // Num flights, sizeof(long) x num flights, flights
            int replySize = (int)(result.size() * PrimitiveSizes.sizeof((long) result.size()) + PrimitiveSizes.sizeof(result.size()));
            for (String flightId : result) {
                replySize += flightId.length();
            }

            replyContent = new byte[replySize];

            int start = 0;

            byte[] numFlights = SerializePOD.serialize(result.size());
            System.arraycopy(numFlights, 0, replyContent, start, numFlights.length);
            start += numFlights.length;

            for (String flightId : result)
            {
                byte[]flightIdBuffer = SerializePOD.serialize(flightId.toCharArray()); 
                System.arraycopy(flightIdBuffer, 0, replyContent, start, flightIdBuffer.length);
                start += flightIdBuffer.length;
            }
        }
        
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();

        Skeleton.storeResponse(replyBuffer, clientIP, port, requestId);
        
        communication.Communication.send(clientIP, port, replyBuffer);
    }
}
