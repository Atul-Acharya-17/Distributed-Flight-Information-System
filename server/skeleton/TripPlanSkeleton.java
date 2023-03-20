package skeleton;

import java.io.IOException;
import java.util.ArrayList;
import java.util.Arrays;

import javax.lang.model.type.PrimitiveType;

import communication.Reply;
import entities.FlightFactoryServant;
import entities.FlightServant;
import entities.TripServant;
import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class TripPlanSkeleton extends Skeleton {
    
    public static void handle(byte[] content, char[] clientIP, int port, int requestId) throws IOException
    {
        int idx = 0;

        String source = new String(SerializePOD.deserializeString(content, idx));
        idx += source.length() + PrimitiveSizes.sizeof((long) source.length());

        String destination = new String(SerializePOD.deserializeString(content, idx));
        idx += destination.length() + PrimitiveSizes.sizeof((long) destination.length());

        int numFlights = SerializePOD.deserializeInt(content, idx);
        idx += PrimitiveSizes.sizeof(numFlights);

        float maxCost = SerializePOD.deserializeFloat(content, idx);
        idx += PrimitiveSizes.sizeof(maxCost);

        FlightFactoryServant fm = new FlightFactoryServant();
        ArrayList<TripServant> result = fm.planTrip(source, destination, numFlights, maxCost);

        short status = 0;
        byte[] replyContent;

        if (result.size() == 0)
        {
            status = 1;
            replyContent = SerializePOD.serialize("No flights found".toCharArray());
        }

        else {
            // encode num trips
            // encode each trip
        }
        
        // Reply reply = new Reply(status, replyContent);

        // byte[] replyBuffer = reply.serialize();

        // communication.Communication.send(new String(clientIP), port, replyBuffer);
    }
}
