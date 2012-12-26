package org.freequant;

import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;

import org.freequant.Bar;
import org.freequant.CtpMarketDataProvider;
import org.freequant.MarketDataProviderCallback;

public class CtpMdTester {
          static private void loadLib(final String name) throws IOException {
                String prefix = "";
                String suffix = "";
                String osName = System.getProperty("os.name");
                if (osName.equals("Linux")) {
                        prefix = "lib";
                        suffix = ".so";

                } else if (osName.substring(0, 7).equals("Windows")) {
                        suffix = ".dll";
                }
                InputStream in = CtpMdTester.class.getResource("/" + prefix + name + suffix).openStream();
                File lib = File.createTempFile(name, suffix);
                FileOutputStream out = new FileOutputStream(lib);

                int i;
                byte[] buf = new byte[1024];
                while ((i = in.read(buf)) != -1) {
                        out.write(buf, 0, i);
                }

                in.close();
                out.close();
                lib.deleteOnExit();
                System.load(lib.toString());
        }

        static {
                try {
                        loadLib("freequant-java");
                } catch (Exception e) {
                        e.printStackTrace();
                }
        }
    private class MdCallback extends MarketDataProviderCallback {
        private Object parent;
        public MdCallback(Object parent) {
                this.parent = parent;
        }

        public void onConnected() {
            System.out.println("onConnected");
        };

        public void onBar(Bar bar) {
                System.out.println(bar.toString());
        };
    }
    private MdCallback mdCallback;
    private CtpMarketDataProvider provider;

    public CtpMdTester() {
    String conn = "protocal=tcp;host=180.168.212.79;port=31213;userid=40022870;password=141537;brokerid=4000";
    provider = new CtpMarketDataProvider(conn, mdCallback);
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
