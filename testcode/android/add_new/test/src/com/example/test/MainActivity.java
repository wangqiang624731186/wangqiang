package com.example.test;

import com.neusoft.ivijni.Jniadd;

import com.neusoft.ivijni.Jniadd.OnAddListener;

import android.os.Bundle;
import android.app.Activity;
import android.view.Menu;
import android.widget.TextView;
import android.os.Handler;
import android.os.Message;


import android.util.Log;


public class MainActivity extends Activity {
        private final String TAG = "MainActivitytest";
        private static final int MSG_ADD = 1;
        private TextView mText;
        private int mNum = 0;
        private int mCount = 0;
        private static final int PTIME_INTERVAL_MS = 1000;

        private Handler handler = new Handler() {
                public void handleMessage(Message msg) {
                        super.handleMessage(msg);
                        switch (msg.what) {
                        case MSG_ADD: {
                               // mNum++;
                                mText.setText(String.valueOf(mNum));
                                System.out.println("in the  java handler" + mNum);
                                //Message message = handler.obtainMessage(MSG_ADD);
                               // handler.sendMessageDelayed(message, PTIME_INTERVAL_MS);
                                break;
                        }
                        default:
                                break;
                        }

                }
        };

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);

                mText = (TextView) this.findViewById(R.id.textViewAdd);
                Log.i(TAG, "Nadd  ------ > ");
        	Jniadd test = new Jniadd();
                Log.i(TAG, "Nadd  < ------  ");

                Log.i(TAG, "nAdd  ------ > ");
                setTitle(String.valueOf(test.nAdd(30, 30)));
                Log.i(TAG, "nAdd  < ------  ");
		test.addListener(new OnAddListener(){
			public void OnAdd(int num)
			{
				System.out.println("in the  java apk" + num);
                                //mText.setText("num111111111111111111");
                                mNum = num;

                               // if(mCount == 0){
                                    System.out.println("in the  java handler1111 : " + mCount);
                                    Message message = handler.obtainMessage(MSG_ADD);
                                    handler.sendMessageDelayed(message, PTIME_INTERVAL_MS);
                               // }
                                  mCount++;


			}
		});
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

}
