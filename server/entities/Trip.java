package entities;

import java.util.ArrayList;

import marshall.Serialization;

public interface Trip extends Serialization {
    public ArrayList<String> getFlights();
    public void setFlights(ArrayList<String> flights);
    
    public float getPrice(); //Price per seat
    public void setPrice(float price);

    public void display();
}
