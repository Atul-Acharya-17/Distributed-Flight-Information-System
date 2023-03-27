package skeleton;
import java.util.ArrayList;

import communication.Reply;

import java.io.IOException;
import java.lang.System;
import entities.Subscriber;
import marshall.SerializePOD;
import utils.PrimitiveSizes;
import entities.FlightFactoryServant;
import entities.Publish;
import entities.PublishFactoryServant;

public class FlightPublisherSkeleton extends Skeleton {
    private static ArrayList<Subscriber> subscribers;

    private static short status;

    public static void handle(byte[] content, String clientIP, int port, int requestId) throws IOException
    {
        int idx = 0;
        String flight_id = new String(SerializePOD.deserializeString(content, idx));
        idx += flight_id.length() + PrimitiveSizes.sizeof((long) flight_id.length());
        int lifetime = SerializePOD.deserializeInt(content, idx);
        long timestamp = System.currentTimeMillis();

        if (Skeleton.checkandRespondToDuplicate(content, clientIP, port, requestId)) 
        {
            Subscriber subscriber = new Subscriber(flight_id, clientIP, port, requestId, lifetime, timestamp);
            subscribers.stream().filter(obj -> subscriber.getSubscriberId().equals(obj.getSubscriberId()))
                    .forEach(s -> s.setStartTimestamp(timestamp));

            return;
        }

        status = subscribe(flight_id, clientIP, port, requestId, lifetime, timestamp);
        byte[] replyContent;
        if (status == 0)
            replyContent = SerializePOD.serialize(clientIP + " " + port + " subscribed to updates successfully");
        else
            replyContent = SerializePOD.serialize("Requested flight not found");
        Reply reply = new Reply(status, replyContent);

        byte[] replyBuffer = reply.serialize();
        communication.Communication.send(clientIP, port, replyBuffer);
    }

    public static short subscribe(String flightID, String clientIp, int port, int requestID, int lifetime, long timestamp)
    {
        FlightFactoryServant ffs = new FlightFactoryServant();
        if (!ffs.checkFlight(flightID)) {
            System.out.println("flight not found");
            return 1;
        }
        if (subscribers == null)
        {
            subscribers = new ArrayList<Subscriber>();
        }
        Subscriber subscriber = new Subscriber(flightID, clientIp, port, requestID, lifetime, timestamp);
        // if (!subscribers.stream().map(Subscriber::getSubscriberId).filter(subscriber::equals).findFirst().isPresent())
        if (!subscribers.stream().anyMatch(obj -> subscriber.getSubscriberId().equals(obj.getSubscriberId())))
        {
            subscribers.add(subscriber);
            System.out.println(
                    clientIp + " " + port + " Subscribed for " + lifetime + " at " + timestamp + " to " + flightID);

        }
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
