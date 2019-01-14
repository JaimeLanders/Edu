import java.util.HashMap;

public class Environment {

	private enum OpType
	{
		ADD, MULTIPLY;
	}

	// todo: declare the data fields
	private HashMap<ElementType,Double> m_elements;

	public Environment()
	{
		m_elements = new HashMap<ElementType,Double>();
		m_elements.put(ElementType.DILITHIUM_VAPOR, 0.002);
		m_elements.put(ElementType.HEXAFLOURINE_GAS, 0.00072);
		m_elements.put(ElementType.HYDRAZINE, 0.000001);
		m_elements.put(ElementType.NITRIUM_GAS, 0.1);
		m_elements.put(ElementType.PROTOMATTER_DENSITY, 0.0000000031);
		m_elements.put(ElementType.TRACE_TRILITHIUM_PARTICULATE, 0.045);
	}

	public double sense(ElementType type)
	{
		double ret = 0.0;

		ret = m_elements.get(type);

		return(ret);
	}

	public void emit(ElementType type,double amount)
	{
		switch (type) {
		case DILITHIUM_VAPOR:
			updateValue(ElementType.DILITHIUM_VAPOR,OpType.ADD,amount);
			updateValue(ElementType.HEXAFLOURINE_GAS,OpType.ADD,amount*0.1);
			updateValue(ElementType.HYDRAZINE,OpType.ADD,-amount*0.1);
			updateValue(ElementType.NITRIUM_GAS,OpType.MULTIPLY,1.001);
			updateValue(ElementType.PROTOMATTER_DENSITY,OpType.MULTIPLY,(1/amount));
			updateValue(ElementType.TRACE_TRILITHIUM_PARTICULATE,OpType.ADD,(-amount/2));
			break;
		case HEXAFLOURINE_GAS:
			updateValue(ElementType.DILITHIUM_VAPOR,OpType.ADD,-amount*0.2);
			updateValue(ElementType.HEXAFLOURINE_GAS,OpType.ADD,amount);
			updateValue(ElementType.HYDRAZINE,OpType.ADD,amount*0.1);
			updateValue(ElementType.NITRIUM_GAS,OpType.MULTIPLY,1.002);
			updateValue(ElementType.PROTOMATTER_DENSITY,OpType.MULTIPLY,(1/amount));
			updateValue(ElementType.TRACE_TRILITHIUM_PARTICULATE,OpType.ADD,(-amount/3));
			break;
		case HYDRAZINE:
			updateValue(ElementType.DILITHIUM_VAPOR,OpType.ADD,-amount);
			updateValue(ElementType.HEXAFLOURINE_GAS,OpType.ADD,-amount*0.1);
			updateValue(ElementType.HYDRAZINE,OpType.ADD,amount);
			updateValue(ElementType.NITRIUM_GAS,OpType.MULTIPLY,0.09);
			updateValue(ElementType.PROTOMATTER_DENSITY,OpType.MULTIPLY,(1/amount));
			updateValue(ElementType.TRACE_TRILITHIUM_PARTICULATE,OpType.ADD,(-amount/4));
			break;
		case NITRIUM_GAS:
			updateValue(ElementType.DILITHIUM_VAPOR,OpType.MULTIPLY,0.9);
			updateValue(ElementType.HEXAFLOURINE_GAS,OpType.MULTIPLY,0.9);
			updateValue(ElementType.HYDRAZINE,OpType.MULTIPLY,0.9);
			updateValue(ElementType.NITRIUM_GAS,OpType.ADD,amount);
			updateValue(ElementType.PROTOMATTER_DENSITY,OpType.MULTIPLY,(1/amount));
			updateValue(ElementType.TRACE_TRILITHIUM_PARTICULATE,OpType.ADD,0);
			break;
		case PROTOMATTER_DENSITY:
			updateValue(ElementType.DILITHIUM_VAPOR,OpType.ADD,-amount);
			updateValue(ElementType.HEXAFLOURINE_GAS,OpType.ADD,-amount);
			updateValue(ElementType.HYDRAZINE,OpType.ADD,-amount);
			updateValue(ElementType.NITRIUM_GAS,OpType.ADD,-amount);
			updateValue(ElementType.PROTOMATTER_DENSITY,OpType.ADD,amount);
			updateValue(ElementType.TRACE_TRILITHIUM_PARTICULATE,OpType.ADD,-amount);
			break;
		case TRACE_TRILITHIUM_PARTICULATE:
			updateValue(ElementType.DILITHIUM_VAPOR,OpType.ADD,amount*0.1);
			updateValue(ElementType.HEXAFLOURINE_GAS,OpType.ADD,amount*0.1);
			updateValue(ElementType.HYDRAZINE,OpType.ADD,-amount*0.1);
			updateValue(ElementType.NITRIUM_GAS,OpType.MULTIPLY,1.001);
			updateValue(ElementType.PROTOMATTER_DENSITY,OpType.MULTIPLY,(1/amount));
			updateValue(ElementType.TRACE_TRILITHIUM_PARTICULATE,OpType.ADD,amount);
			break;
		}
	}

	private void updateValue(ElementType type,OpType opType, double modValue)
	{
		double oldValue;
		double newValue;

		oldValue = m_elements.get(type);

		if (opType == OpType.ADD)
			newValue = oldValue + modValue;
		else
			newValue = oldValue * modValue;

		m_elements.replace(type,newValue);
	}
}
