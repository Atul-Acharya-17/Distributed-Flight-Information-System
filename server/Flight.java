import java.rmi.*;

public interface Flight extends Remote {

    public String getFlightID() throws RemoteException;
    public void setFlightID(String flightID) throws RemoteException;

    public String getSource() throws RemoteException;
    public void setSource(String source) throws RemoteException;

    public String getDestination() throws RemoteException;
    public void setDestination(String destination) throws RemoteException;

    public int getSeatsAvailable() throws RemoteException;
    public void setSeatsAvailable(int seatsAvailable) throws RemoteException;

    public int getSeatsBooked() throws RemoteException;
    public void setSeatsBooked(int seatsBooked) throws RemoteException;
    
    public float getPrice() throws RemoteException; //Price per seat
    public void setPrice(float price) throws RemoteException;

}