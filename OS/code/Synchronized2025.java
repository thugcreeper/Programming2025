public class Main {
	
	// version 1, 2, 3
	// int x;
	// version 4
	static int x;
	
	public static void main(String[] args) {		
		Main main = new Main();
		main.exec();
	}
	
	void exec() {
		
    	this.x = 3;
		
		AddThread t1 = new AddThread(this, 1);
		AddThread t2 = new AddThread(this, 2);
		
		t1.start();
		t2.start();
		try {
			Thread.sleep(6000);
		} catch (InterruptedException e) {
		}		
		System.out.println(x);		
	}
	
	// version 3: addX is moved to Main class with synchronized
	/*
	synchronized void addX(int addValue) {
		int localX = x;
		localX += addValue;			
		long milliseconds = (long)(Math.random()*3000);
		System.out.println("addValue: " + addValue +
				", milliseconds: " + milliseconds);
		try {
			Thread.sleep(milliseconds);
		} catch (InterruptedException e) {
		}
		x = localX;
	}
	*/

	class AddThread extends Thread {
		
		int addValue = 0;
		Main main;
		
		public AddThread(Main main, int addValue) {
			this.addValue = addValue;
			this.main = main;
		}
		
		@Override
		public void run() {
			// version 1: addX is defined in AddThread class w/o synchronized
			// version 2: addX is defined in AddThread class with synchronized
			// version 4: version 2 + static
			this.addX(addValue);

            // version 3: addX is moved to Main class with synchronized
			// main.addX(addValue);
		}
		
		// version 1: addX is defined in AddThread class w/o synchronized
		// void addX(int addValue) {
		// version 2: addX is defined in AddThread class with synchronized
		// synchronized static void addX(int addValue) {
		// version 3: addX is moved to Main class with synchronized
		// version 4: version 2 + static
		synchronized static void addX(int addValue) {
			int localX = x;
			localX += addValue;			
			long milliseconds = (long)(Math.random()*3000);
			System.out.println("addValue: " + addValue +
				", milliseconds: " + milliseconds);
			try {
				Thread.sleep(milliseconds);
			} catch (InterruptedException e) {
			}
			x = localX;
		}
	}
}