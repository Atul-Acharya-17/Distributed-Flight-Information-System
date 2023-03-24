package entities;

import java.sql.Timestamp;
import java.util.ArrayList;
import java.lang.System;
import entities.FlightServant;
import entities.Flight;

public class PublisherServant {
    private static ArrayList<Subscriber> subscribers;

    public String publishCancellation(String FlightID, int numSeatsCancelled, int updatedNumSeats)
    {
        String msg = numSeatsCancelled + " new seats available for flight " + FlightID + "\n";
        msg += "Total seats available for flight " + FlightID + " = " + updatedNumSeats + " :\n";
        return msg;
    }

    public String publishBooking(String FlightID, int numSeatsBooked, int updatedNumSeats) {
        String msg = numSeatsBooked + " seats booked for flight " + FlightID + "\n";
        msg += "Total seats available for flight " + FlightID + " = " + updatedNumSeats + " :\n";
        return msg;
    }

    public Boolean isSubscriberAlive(Subscriber sub)
    {
        long currTime = System.currentTimeMillis();
        long subLife = sub.getStartTimestamp() + sub.getLifetime() * 1000; //converting seconds to ms
        if (currTime < subLife)
            return true;
        else
            return false;
    }
}
