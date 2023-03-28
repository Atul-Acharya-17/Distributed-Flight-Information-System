package entities;

public class Subscriber {
    private String monitorFlight;
    private String clientIp;
    private int port;
    private int requestID;
    private int lifetime;
    private long startTimestamp;
    private String subscriberId;

    public Subscriber(String flightID, String clientIp, int port, int requestId, int lifetime, long startTimestamp)
    {
        this.monitorFlight = flightID;
        this.clientIp = clientIp;
        this.port = port;
        this.requestID = requestId;
        this.lifetime = lifetime;
        this.startTimestamp = startTimestamp;
        this.subscriberId = this.clientIp + this.port + this.monitorFlight;
    }

    public String getMonitorFlight()
    {
        return monitorFlight;
    }

    public long getLifetime() {
        return lifetime;//in seconds
    }

    public String getClientIp() {
        return clientIp;
    }

    public int getPort() {
        return port;
    }

    public long getStartTimestamp()
    {
        return startTimestamp;
    }

    public void setStartTimestamp(long timestamp)
    {
        this.startTimestamp = timestamp;
    }

    public int getRequestId()
    {
        return requestID;
    }

    public String getSubscriberId()
    {
        return subscriberId;
    }
}
