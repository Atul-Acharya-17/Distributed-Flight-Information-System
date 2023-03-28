package marshall;

import java.io.IOException;


/* 
    Interface for every object to implement
    We make the objects responsible for marshalling and unmarshalling themselves
*/ 

public interface Serialization {
    public void deserialize(byte[] dataIn);
    public byte[] serialize() throws IOException;
    public long size(); 
}
