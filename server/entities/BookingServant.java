package entities;
import java.io.IOException;

import marshall.SerializePOD;
import utils.PrimitiveSizes;
import utils.Utils;

public class BookingServant implements Booking {
    private char[] bookingId;
    private char[] flightId;
    private char[] clientId;
    private int numSeatsBooked;

    public BookingServant(char[] bookingId, char[] flightId, char[] clientId, int numSeatsBooked) {
        this.bookingId = bookingId;
        this.flightId = flightId;
        this.clientId = clientId;
        this.numSeatsBooked = numSeatsBooked;
    }

    public BookingServant(char[] flightId, char[] clientId, int numSeatsBooked) {
        this.bookingId = Utils.generateRandomAlphanumericString(6).toCharArray();
        this.flightId = flightId;
        this.clientId = clientId;
        this.numSeatsBooked = numSeatsBooked;
    }

    public char[] getBookingId() {
        return bookingId;
    }
  
    public void setBookingId(char[] bookingId) {
        this.bookingId = bookingId;
    }

    public char[] getFlightId() {
        return flightId;
    }

    public void setFlightId(char[] flightId) {
        this.flightId = flightId;
    }

    public char[] getClientId() {
        return clientId;
    }

    public void setClientId(char[] clientId) {
        this.clientId = clientId;
    }

    public int getNumSeatsBooked() {
        return numSeatsBooked;
    }

    public void setNumSeatsBooked(int numSeatsBooked) {
        this.numSeatsBooked = numSeatsBooked;
    }

    @Override
    public void display() {
        System.out.print(new String(bookingId) + " @ " + new String(flightId) + 
                        " <---> " + new String(clientId) + " # " + numSeatsBooked + "\n");
    }

    @Override
    public long size() {
        return (
            PrimitiveSizes.sizeof((long)bookingId.length) + bookingId.length +
            PrimitiveSizes.sizeof((long)flightId.length) + flightId.length + 
            PrimitiveSizes.sizeof((long)clientId.length) + clientId.length +
            PrimitiveSizes.sizeof(numSeatsBooked)
        );
    }

    @Override
    public void deserialize(byte[] dataIn) {
        int start = 0;
        
        bookingId = SerializePOD.deserializeString(dataIn, start);
        long bookingIdSize = bookingId.length;
        start += bookingIdSize + PrimitiveSizes.sizeof(bookingIdSize);
        
        flightId = SerializePOD.deserializeString(dataIn, start);
        long flightIdSize = flightId.length;
        start += flightIdSize + PrimitiveSizes.sizeof(flightIdSize);

        clientId = SerializePOD.deserializeString(dataIn, start);
        long clientIdSize = clientId.length;
        start += clientIdSize + PrimitiveSizes.sizeof(clientIdSize);

        numSeatsBooked = SerializePOD.deserializeInt(dataIn, start);
        start += PrimitiveSizes.sizeof(numSeatsBooked);
    }

    public byte[] serialize() throws IOException {
        byte[] buffer = new byte[(int)this.size()];

        System.out.println(flightId);

        byte[] bookingIdBuffer = SerializePOD.serialize(bookingId);
        byte[] flightIdBuffer = SerializePOD.serialize(flightId);
        byte[] clientIdBuffer = SerializePOD.serialize(clientId);
        byte[] numSeatsBookedBuffer = SerializePOD.serialize(numSeatsBooked);

        int i = 0;
        System.arraycopy(bookingIdBuffer, 0, buffer, i, bookingIdBuffer.length);
        i += bookingIdBuffer.length;
        System.arraycopy(flightIdBuffer, 0, buffer, i, flightIdBuffer.length);
        i += flightIdBuffer.length;
        System.arraycopy(clientIdBuffer, 0, buffer, i, clientIdBuffer.length);
        i += clientIdBuffer.length;
        System.arraycopy(numSeatsBookedBuffer, 0, buffer, i, numSeatsBookedBuffer.length);
        i += numSeatsBookedBuffer.length;

        return buffer;
    }

}

