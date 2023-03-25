package skeleton;

import java.sql.Timestamp;
import java.util.ArrayList;

import communication.Reply;

import java.io.IOException;
import java.lang.System;
import entities.Subscriber;
import marshall.SerializePOD;
import utils.PrimitiveSizes;
import entities.Flight;
import entities.FlightFactoryServant;
import entities.Publish;
import entities.PublishFactoryServant;

public class FlightPublisher extends Skeleton {
    private static ArrayList<Subscriber> subscribers;

    private static short status;

    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        // 
        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId))
            return;
        
        int idx = 0;
        String flight_id = new String(SerializePOD.deserializeString(content, idx));
        idx += flight_id.length() + PrimitiveSizes.sizeof((long) flight_id.length());
        int lifetime = SerializePOD.deserializeInt(content, idx);
        long timestamp = System.currentTimeMillis();
        status = subscribe(flight_id, clientIP, port, requestId, lifetime, timestamp);
    }

    public static short subscribe(String flightID, String clientIp, int port, int requestID, int lifetime, long timestamp)
    {
        if (subscribers == null)
        {
            subscribers = new ArrayList<Subscriber>();
        }
        subscribers.add(new Subscriber(flightID, clientIp, port, requestID, lifetime, timestamp));
        System.out.println(clientIp + " " + port + " Subscribed");
        return 0;
    }

    public static short unsubscribe(Subscriber sub)
    {
        subscribers.remove(sub);
        System.out.println(sub.getClientIp() + " " + sub.getPort() + " unubscribed");
        return 0;
    }

    public static Boolean isSubscriberAlive(Subscriber sub) {
        long currTime = System.currentTimeMillis();
        long subLife = sub.getStartTimestamp() + sub.getLifetime() * 1000; // converting seconds to ms
        if (currTime < subLife)
            return true;
        else
            return false;
    }

    public static void publish(String flightID) throws IOException
    {
        byte[] replyContent;
        while (true)
        {
            Publish publish = PublishFactoryServant.getPublish();
            replyContent = publish.serialize();
            if (subscribers.size() > 0)
                for (Subscriber subscriber : subscribers) {
                    if (isSubscriberAlive(subscriber)) {
                        // Send via Communication
                        if (subscriber.getMonitorFlight() == flightID)
                        {
                            Reply reply = new Reply(status, replyContent);

                            byte[] replyBuffer = reply.serialize();

                            Skeleton.storeResponse(replyBuffer, subscriber.getClientIp(), subscriber.getPort(), subscriber.getRequestId());

                            communication.Communication.send(subscriber.getClientIp(), subscriber.getPort(), replyBuffer);
                        }
                    } else {
                        // Remove subscriber from the list
                        unsubscribe(subscriber);
                    }
                }
        }
        
    }
}
