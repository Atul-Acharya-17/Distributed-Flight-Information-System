package entities;

import marshall.Serialization;

/* 
    Interface for a Publisher object to generate update message whenever a booking is made/cancelled.
    Inherits from Serializable which allows to serialize objects.
*/
public interface Publish extends Serialization {
    
    public char[] getMsg();

    public void setMsg(char[] msg);
}
