
package com.example.jnitest;
                                       
import com.neusoft.c3alfus.rpc.NativeRpc;
import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import com.neusoft.c3alfus.rpc.NativeRpc.OnRpcListener;


public class MainActivity extends Activity {
	NativeRpc test;
	@Override
    public void onCreate(Bundle savedInstanceState) {

        super.onCreate(savedInstanceState);

        setContentView(R.layout.activity_main);
        int ret = 0;
		
        test = NativeRpc.getInstance();
		
		System.out.println("MainActivity onCreate");
		System.out.println("after test attach \n");
		byte [] dataIn = new byte[25];
		byte control = 0x00;
		short opecode = 0x0508;

		byte i = 0;
		for(i = 0; i< 25; i++)
		{
			dataIn[i] = i;
		}
		
		ret = test.sendCmd(control, opecode, dataIn);
		System.out.println(" sendCmd 0x0508 APK send result : ***************");
		System.out.println(ret);
		
		opecode = 0x0508;
		ret = test.sendCmd(control, opecode, dataIn);
		System.out.println(" sendCmd 0x0508 APK send result : ***************");
		System.out.println(ret);
		
		opecode = 0x0508;
		byte[] outdata = new byte[25];
		outdata = test.getInfo(control, opecode, dataIn);
		System.out.println(" getInfo 0x0508 APK send result : ************");
		for(i = 0; i< 25; i++)
		{
			System.out.println(" 0x0508 APK send result : ************"+ outdata[i]);
		}
		//mVal = (TextView) row.findViewById(R.id.row_textview_value);
		test.registerListener(NativeRpc.NEU_C3_ALFUS_RPC_CALLBACK_TYPE_ALL, new OnRpcListener(){
			public void onCallback	(byte length, byte control, short opecode,byte[] dataOut)
			{	
				System.out.println("ALL listener1 in the  java apk" );
				System.out.println("length , control ,opecode :" );
				System.out.println(length );
				System.out.println(control );
				System.out.println(opecode );
				int j = 0;
				for(j = 0; j< 25; j++)
				{
					System.out.println(dataOut[j]);
				}
				//mVal.setText(String.valueOf(num));
			}
		});
		test.registerListener("SYSTEM", new OnRpcListener(){
			public void onCallback	(byte length, byte control, short opecode,byte[] dataOut)
			{	
				System.out.println("SYSTEM listener2 in the  java apk" );
				System.out.println("length , control ,opecode :" );
				System.out.println(length );
				System.out.println(control );
				System.out.println(opecode );
				int j = 0;
				for(j = 0; j< 25; j++)
				{
					System.out.println(dataOut[j]);
				}
				//mVal.setText(String.valueOf(num));
			}
		});
    } 
    @Override
    public void onDestroy() {
		System.out.println("MainActivity onDestroy");
		test.unRegisterListener();
		super.onDestroy();
		
	}
	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
