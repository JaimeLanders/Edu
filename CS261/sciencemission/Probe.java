import java.util.*;

public class Probe 
{
    private List<Sensor> sensorList = new LinkedList<>();
    private List<Emitter> emitterList = new LinkedList<>();
    
    private String probeName;

    public Probe(Scanner sc)
    {
        while (sc.hasNext())
        {
            String temp = sc.next();

            if(temp.equals("END"))
                break;

            if (temp.equals("SENSOR"))
            {
                Sensor nSensor = new Sensor(sc);
                sensorList.add(nSensor);
            }
            if (temp.equals("EMITTER"))
            {
                Emitter nEmitter = new Emitter(sc);
                emitterList.add(nEmitter);
            }
        }
    }

    public void activateProbe(Environment envIn)
    {
        System.out.println("Probe " + this.probeName +  " starting ");
        System.out.println("Sensor reading's before emitting ");
        for (Sensor n : sensorList)
        {
            n.setValue(envIn.sense(n.getElement()));
            System.out.println("  Last reading for " + n.getElement() + ": " + n.getValue());
        }
        for (Emitter n : emitterList)
        {
            System.out.println("  Emitting a burst of " + n.getValue() + "units of " + n.getElement());
            envIn.emit(n.getElement(), n.getValue());
        }
            System.out.println("Sensor reading's after emitting ");
        for (Sensor n : sensorList)
        {
            n.setValue(envIn.sense(n.getElement()));
            System.out.println("  Last reading for " + n.getElement() + ": " + n.getValue());
        }
        
    }

    public void launchProbe()
    {
        System.out.println("Launching Probe " + this.getName());
        System.out.println("------------------------------------------------ ");
    }

    public String getName()
    {
        return this.probeName;
    }

    public void recallProbe()
    {
        System.out.println("Recalling Probe " + this.getName());
    }

    public void setName(String probeIn)
    {
        this.probeName = probeIn;
    }

}
