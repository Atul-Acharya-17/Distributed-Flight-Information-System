package entities;

public class Subscriber {
    private String clientIp;
    private int port;
    private long timestamp;

    public Subscriber(String clientIp, int port, long timestamp)
    {
        this.clientIp = clientIp;
        this.port = port;
        this.timestamp = timestamp;
    }

    public long getTimestamp() {
        return timestamp;
    }

    public String getClientIp() {
        return clientIp;
    }

    public int getPort() {
        return port;
    }
}
