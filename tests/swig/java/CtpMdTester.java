package org.freequant;

import org.freequant.Bar;
import org.freequant.CtpMarketDataProvider1;
import org.freequant.MarketDataProviderCallback;

public class CtpMdTester {
    private class MdCallback extends MarketDataProviderCallback {
    	private Object parent;
    	public MdCallback(Object parent) {
    		this.parent = parent;
    	}
    	
    	public void onConnected() {
    		
    	};
    	
    	public void onBar(Bar bar) {
    		System.out.println(bar.toString());
    	};
    }
    private MdCallback mdCallback;
    private CtpMarketDataProvider1 provider;
    
    public CtpMdTester() {
    	mdCallback = new MdCallback(this);
    	provider = new CtpMarketDataProvider1("", mdCallback);
    	provider.connect();
    	provider.subscribe("IF1301");
    }
    
    @SuppressWarnings("static-access")
	public void run() {
    	while (true) {
    		Thread.currentThread().yield();
    	}
    }
	public static void main(String[] args) {
		new CtpMdTester().run();
	}

}

