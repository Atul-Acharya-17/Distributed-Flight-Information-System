package skeleton;
import java.util.ArrayList;

import communication.Reply;

import java.io.IOException;
import java.lang.System;
import entities.Subscriber;
import marshall.SerializePOD;
import utils.PrimitiveSizes;
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
        byte[] replyContent = SerializePOD.serialize(clientIP + " " + port + " subscribed to updates successfully");
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();
        communication.Communication.send(clientIP, port, replyBuffer);
    }

    public static short subscribe(String flightID, String clientIp, int port, int requestID, int lifetime, long timestamp)
    {
        if (subscribers == null)
        {
            subscribers = new ArrayList<Subscriber>();
        }
        subscribers.add(new Subscriber(flightID, clientIp, port, requestID, lifetime, timestamp));
        System.out.println(clientIp + " " + port + " Subscribed for " + lifetime + " at " + timestamp + " to " + flightID);
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
        long endLife = sub.getStartTimestamp() + sub.getLifetime() * 1000; // converting seconds to ms
        if (currTime < endLife)
            return true;
        else
            return false;
    }

    public static void publish(String flightID) throws IOException
    {
        byte[] replyContent;
        
        Publish publish = PublishFactoryServant.getPublish();
        System.out.println(publish.getMsg());
        replyContent = publish.serialize();

        
        if (subscribers!=null && subscribers.size() > 0) {
            ArrayList<Subscriber> subscribers_temp = (ArrayList<Subscriber>) subscribers.clone();
            for (Subscriber subscriber : subscribers_temp) {
                if (isSubscriberAlive(subscriber)) {
                    // Send via Communication
                    if (subscriber.getMonitorFlight().compareTo(flightID)==0)
                    {
                        Reply reply = new Reply(status, replyContent);

                        byte[] replyBuffer = reply.serialize();

                        System.out.println("Sent update message to " + subscriber.getClientIp() + ":" + subscriber.getPort() + "---" + publish.getMsg().toString());
                        communication.Communication.send(subscriber.getClientIp(), subscriber.getPort(), replyBuffer);
                    }
                } else {
                    // Remove subscriber from the list
                    unsubscribe(subscriber);
                    if (subscribers == null)
                        break;
                }
            }
        }       
        
    }
}
