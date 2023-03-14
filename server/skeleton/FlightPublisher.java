package skeleton;

import java.sql.Timestamp;
import java.util.ArrayList;

import entities.Subscriber;

public class FlightPublisher {
    private static ArrayList<Subscriber> subscribers;

    public static void subscribe(String clientIp, int port, long timestamp)
    {
        subscribers.add(new Subscriber(clientIp, port, timestamp));
    }

    public static void publish(byte[] message)
    {
        long currentTimestamp = System.currentTimeMillis();

        for (Subscriber subscriber : subscribers) 
        {
            if (subscriber.getTimestamp() <= currentTimestamp)
            {
                // Send via Communication
            }
            else
            {
                // Remove subscriber from the  list
            }
        }
    }
}