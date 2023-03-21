package entities;
import java.io.IOException;
import java.sql.Time;
import java.time.LocalTime;
import java.util.Date;

import marshall.SerializePOD;
import utils.PrimitiveSizes;

public class FlightServant implements Flight {
    private char[] flightId;
    private char[] source;
    private char[] destination;
    private int seatsAvailable;
    private int seatsBooked;
    private float price;
    private LocalTime departureTime;
    private LocalTime duration;

    @Override
    public long size() {
        return (
            PrimitiveSizes.sizeof((long)flightId.length) + flightId.length + 
            PrimitiveSizes.sizeof((long)source.length) + source.length +
            PrimitiveSizes.sizeof((long)destination.length) + destination.length +
            PrimitiveSizes.sizeof(seatsAvailable) + 
            PrimitiveSizes.sizeof(seatsBooked) + 
            PrimitiveSizes.sizeof(price)
        );
    }

    public FlightServant()
    {
        
    }

    public FlightServant(char[] flightId, char[] source, char[] destination, int seatsAvailable, int seatsBooked, float price, LocalTime departureTime, LocalTime duration) {
        this.flightId = flightId;
        this.source = source;
        this.destination = destination;
        this.seatsAvailable = seatsAvailable;
        this.seatsBooked = seatsBooked;
        this.price = price;
        this.duration = duration;
        this.departureTime = departureTime;
    }

    public char[] getFlightId() {
        return flightId;
    }

    public void setFlightId(char[] flightId) {
        this.flightId = flightId;
    }

    public char[] getSource() {
        return source;
    }

    public void setSource(char[] source) {
        this.source = source;
    }

    public char[] getDestination() {
        return destination;
    }

    public void setDestination(char[] destination) {
        this.destination = destination;
    }

    public int getSeatsAvailable() {
        return seatsAvailable;
    }

    public void setSeatsAvailable(int seatsAvailable) {
        this.seatsAvailable = seatsAvailable;
    }

    public int getSeatsBooked() {
        return seatsBooked;
    }

    public void setSeatsBooked(int seatsBooked) {
        this.seatsBooked = seatsBooked;
    }

    public float getPrice() {
        return price;
    }

    public void setPrice(float price) {
        this.price = price;
    }

    public LocalTime getDepartureTime() {
        return this.departureTime;
    }
    public void setDepartureTime(LocalTime departureTime) {
        this.departureTime = departureTime;
    }

    public LocalTime getDuration() {
        return this.duration;
    }

    public void setDuration(LocalTime duration) {
        this.duration = duration;
    }

    @Override
    public void display() {
        System.out.print(new String(flightId) + " @ " + new String(source) + " --> " + new String(destination) + "\n");
        System.out.print(seatsAvailable + " - " + seatsBooked + " # " + price + "\n");
        System.out.println(departureTime + " " + duration);
    }

    @Override
    public void deserialize(byte[] dataIn) {
        int start = 0;
        
        flightId = SerializePOD.deserializeString(dataIn, start);
        long flightIdSize = flightId.length;
        start += flightIdSize + PrimitiveSizes.sizeof(flightIdSize);

        source = SerializePOD.deserializeString(dataIn, start);
        long sourceSize = source.length;
        start += sourceSize + PrimitiveSizes.sizeof(sourceSize);

        destination = SerializePOD.deserializeString(dataIn, start);
        long destinationSize = destination.length;
        start += destinationSize + PrimitiveSizes.sizeof(destinationSize);

        seatsAvailable = SerializePOD.deserializeInt(dataIn, start);
        start += PrimitiveSizes.sizeof(seatsAvailable);

        seatsBooked = SerializePOD.deserializeInt(dataIn, start);
        start += PrimitiveSizes.sizeof(seatsBooked);

        price = SerializePOD.deserializeFloat(dataIn, start);
        start += PrimitiveSizes.sizeof(price);
    }

    public byte[] serialize() throws IOException {
        byte[] buffer = new byte[(int)this.size()];

        byte[] flightIdBuffer = SerializePOD.serialize(flightId);
        byte[] sourceBuffer = SerializePOD.serialize(source);
        byte[] destinationBuffer = SerializePOD.serialize(destination);
        byte[] seatsAvailableBuffer = SerializePOD.serialize(seatsAvailable);
        byte[] seatsBookedBuffer = SerializePOD.serialize(seatsBooked);
        byte[] priceBuffer = SerializePOD.serialize(price);

        int i = 0;
        System.arraycopy(flightIdBuffer, 0, buffer, i, flightIdBuffer.length);
        i += flightIdBuffer.length;
        System.arraycopy(sourceBuffer, 0, buffer, i, sourceBuffer.length);
        i += sourceBuffer.length;
        System.arraycopy(destinationBuffer, 0, buffer, i, destinationBuffer.length);
        i += destinationBuffer.length;
        System.arraycopy(seatsAvailableBuffer, 0, buffer, i, seatsAvailableBuffer.length);
        i += seatsAvailableBuffer.length;
        System.arraycopy(seatsBookedBuffer, 0, buffer, i, seatsBookedBuffer.length);
        i += seatsBookedBuffer.length;
        System.arraycopy(priceBuffer, 0, buffer, i, priceBuffer.length);
        i += priceBuffer.length;

        return buffer;
    }

}

