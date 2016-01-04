package com.example.airplane;

import android.os.Bundle;
import android.os.UserHandle;
import android.provider.Settings;
import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.view.Menu;

import android.content.Context;
import android.content.Intent;
import android.database.ContentObserver;
import android.os.Handler;
import android.os.Message;
import android.os.UserHandle;
import android.preference.CheckBoxPreference;
import android.preference.Preference;
import android.provider.Settings;


public class MainActivity extends Activity {

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        
        
    }
		protected void onStart() {
		     super.onStart();
			 System.out.println("11111111111111111111");
			 android.provider.Settings.System.putInt(this.getContentResolver(), Settings.ACTION_AIRPLANE_MODE_SETTINGS, 1);
			 // Post the intent
			 System.out.println("121111111111111111111");
			 Intent intent = new Intent(Intent.ACTION_AIRPLANE_MODE_CHANGED);
			 intent.putExtra("state", true);
		     this.sendBroadcast(intent);
			 System.out.println("113111111111111111111");
		}

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.main, menu);
        return true;
    }
    
}
