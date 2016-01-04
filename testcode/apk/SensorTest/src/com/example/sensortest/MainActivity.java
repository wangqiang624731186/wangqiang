package com.example.sensortest;


import java.io.BufferedOutputStream;
import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;






import java.util.Timer;
import java.util.TimerTask;

import android.annotation.SuppressLint;
import android.annotation.TargetApi;
import android.app.Activity;
import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.location.GpsSatellite;
import android.location.GpsStatus;
import android.location.GpsStatus.NmeaListener;
import android.location.Location;
import android.location.LocationListener;
import android.location.LocationManager;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.WindowManager;
import android.widget.Button;
import android.widget.TableLayout;
import android.widget.TableRow;
import android.widget.TextView;

public class MainActivity extends Activity {
    private static final String TAG = "testSensors";
    private List<TableRow> mRaw;
    private List<TextView> mVal;
    private TableLayout mTableLayout;
    private Handler mHandler;
    private LocationManager mLocationManager;
    private List<MonitoredSensor> mSensors;
    private List<String> filename;
    private List<dbHelper> dbname;  
    private int SENSOR_SIZE = 0;         

    private final Timer timer = new Timer();
    private TimerTask task;
    
    private static final int TEN_SECONDS = 1000;
    private static final int TEN_METERS = 1;
    private static final int TWO_MINUTES = 1000 * 60 * 2;
    
    private static final int UPDATE_TIME = 0;    
    private static final int UPDATE_LONGITUDE = 1;   
    private static final int UPDATE_LATITUDE = 2;   
    private static final int UPDATE_ALTITUDE = 3;
    private static final int UPDATE_ELAPSE = 4;   
    private static final int UPDATE_SPEED = 5;   
    private static final int UPDATE_BEAR = 6;  
    private static final int UPDATE_ACCURACY = 7;     
    private static final int UPDATE_COUNT = 8;  
    private static final int UPDATE_NMEA = 9;  
  
    private static final int UPDATE_MAX = 10; 
    private static final int UPDATE_TIMER = 11; 
    
    private long startTimeMillis = 0;
    private long totaltime = 0;
    
	private Button actionButton;
	private TextView timeText;
	
	private boolean ui_flag = false;
	
    private class MonitoredSensor implements SensorEventListener {
        private final Sensor mSensor;
        int update_flag = 256;
        private TextView mName;
		long start = System.currentTimeMillis();
        /**
         * Constructs MonitoredSensor instance, and register the listeners.
         *
         * @param sensor Sensor to monitor.
         */
        @SuppressWarnings("deprecation")
		MonitoredSensor(Sensor sensor,int n) {
            mSensor = sensor;
            update_flag = n;
            mName = (TextView) mRaw.get(n).findViewById(R.id.row_textview_name);
    		switch(mSensor.getType()){
        		case Sensor.TYPE_ACCELEROMETER:	    			
        			mName.setText("Acc");
	                break;
	            case Sensor.TYPE_MAGNETIC_FIELD:
        			mName.setText("Mag");
	                break;
	            case Sensor.TYPE_ORIENTATION:
        			mName.setText("Orie");
	                break;
	            case Sensor.TYPE_GYROSCOPE:
        			mName.setText("Gyro");
	                break;
	            case Sensor.TYPE_LIGHT:
        			mName.setText("Light");
	                break;
	            case Sensor.TYPE_PRESSURE:
        			mName.setText("Press");
	                break;		               	                
        		case Sensor.TYPE_TEMPERATURE:	    			
        			mName.setText("Temp");
	                break;
	            case Sensor.TYPE_PROXIMITY:
        			mName.setText("Prox");
	                break;
	            case Sensor.TYPE_GRAVITY:
        			mName.setText("Grav");
	                break;
	            case Sensor.TYPE_LINEAR_ACCELERATION:
        			mName.setText("Liner");
	                break;
	            case Sensor.TYPE_ROTATION_VECTOR:
        			mName.setText("Vector");
	                break;
	            case Sensor.TYPE_RELATIVE_HUMIDITY:
        			mName.setText("Humi");
	                break;	                
        		case Sensor.TYPE_AMBIENT_TEMPERATURE:	    			
        			mName.setText("AmbTemp");
	                break;
	            case Sensor.TYPE_MAGNETIC_FIELD_UNCALIBRATED:
        			mName.setText("MagUnc");
	                break;
	            case Sensor.TYPE_GAME_ROTATION_VECTOR:
        			mName.setText("PotaVec");
	                break;
	            case Sensor.TYPE_GYROSCOPE_UNCALIBRATED:
        			mName.setText("GyroUnc");
	                break;
	            case Sensor.TYPE_SIGNIFICANT_MOTION:
        			mName.setText("Motion");
	                break;		                		                		               	                
	            default:
	            	mName.setText("Unkown");
            }
    		filename.set(update_flag, (String) mName.getText());
        }         			            	
        private int getType() {
            return mSensor.getType();
        }
        /**
         * Starts monitoring the sensor. NOTE: This method is called from
         * outside of the UI thread.
         */
        private void startListening() {
            SensorManager sm = (SensorManager) getSystemService(SENSOR_SERVICE);
            sm.registerListener(this, mSensor, SensorManager.SENSOR_DELAY_UI);
        }

        /**
         * Stops monitoring the sensor. NOTE: This method is called from outside
         * of the UI thread.
         */
        private void stopListening() {
            SensorManager sm = (SensorManager) getSystemService(SENSOR_SERVICE);
            sm.unregisterListener(this);
        }

        /**
         * Handles "sensor changed" event. This is an implementation of the
         * SensorEventListener interface.
         */
        @Override
        public void onSensorChanged(SensorEvent event) {
			long end = System.currentTimeMillis();
			if(end -start > 500)
				start = end;
			else
				return;
			
            final int nArgs = event.values.length;
            String val = "";
            for(int i = 0 ; i < nArgs; i++)
            	val += String.valueOf(event.values[i]) + "    ";
            Message.obtain(mHandler,update_flag,val).sendToTarget();
        }
        @Override
        public void onAccuracyChanged(Sensor sensor, int accuracy) {
        }
    }
 

    /** Called when the activity is first created. */
    @SuppressLint("HandlerLeak")
	@Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        getWindow().addFlags(WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON);
        timeText = (TextView) this.findViewById(R.id.textView0);
        actionButton =  (Button)this.findViewById(R.id.action);
        actionButton.setText("start");

        
        OnClickListener actionButtonListener = new OnClickListener() {
			@Override
			public void onClick(View v) {
				if(ui_flag == true)
				{
					ui_flag = false;
					actionButton.setText("start");	
					startTimeMillis = System.currentTimeMillis();
				}
				else
				{
					actionButton.setText("stop");
                	long currentTimeMillis = System.currentTimeMillis();
                	
                	String time = String.valueOf(currentTimeMillis);  
                	if(startTimeMillis == 0 || currentTimeMillis - startTimeMillis > 10000)
					{
                		dbname.clear();
                		for (int n = 0; n < filename.size() ;n++) {		                	
		                	dbname.add(new dbHelper(MainActivity.this,(String) filename.get(n) + time,null,1));
                		}
					}
            		startTimeMillis = currentTimeMillis;
					ui_flag = true;
				}			
			}
		};
		actionButton.setOnClickListener(actionButtonListener);
		
        mTableLayout = (TableLayout) findViewById(R.id.tableLayout);
        // Iterate through the available sensors, adding them to the array
        new Thread(new MyThread()).start();

        
        mHandler = new Handler() {
            public void handleMessage(Message msg) {

                if(msg.what <= SENSOR_SIZE + UPDATE_MAX && ui_flag == true)            	 
                {
                	mVal.get(msg.what).setText((String) msg.obj);
                	long currentTimeMillis = System.currentTimeMillis();
                	String time = String.valueOf(currentTimeMillis);
                	mVal.get(SENSOR_SIZE + UPDATE_MAX).setText( time);
                	
        			String str = time + "   "  +(String) msg.obj;
        			dbname.get(msg.what).insert( str);
                }
                else if(msg.what == SENSOR_SIZE + UPDATE_TIMER)
                {
                	totaltime++;
                	timeText.setText(String.valueOf(totaltime));
                }
            }
        };
 
        mSensors = new ArrayList<MonitoredSensor>();
        SensorManager sm = (SensorManager) getSystemService(SENSOR_SERVICE);
        List<Sensor> sensors = sm.getSensorList(Sensor.TYPE_ALL);
        SENSOR_SIZE =  sensors.size();  
        
                
        mRaw = new ArrayList<TableRow>();
        mVal = new ArrayList<TextView>();
        filename = new ArrayList<String>();
        dbname = new ArrayList<dbHelper>();
        addView(SENSOR_SIZE);
    


        for (int n = 0; n < sensors.size(); n++) {
            Sensor avail_sensor = sensors.get(n);
            Sensor def_sens = sm.getDefaultSensor(avail_sensor.getType());
            MonitoredSensor to_add = new MonitoredSensor(def_sens,n);
            mSensors.add(to_add);
            to_add.startListening();         
        }
        
        mLocationManager = (LocationManager) getSystemService(Context.LOCATION_SERVICE);
        if(mLocationManager!= null)
        {
        	mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, 1000, 1, locationListener);  
        	//mLocationManager.addGpsStatusListener(GpsStatuslistener);
        	mLocationManager.addNmeaListener(Nmealistener);       	
        	
        }
      
    }

    private TableRow getRaw()
    {
	    final LayoutInflater inflater = getLayoutInflater();
	    final TableRow row = (TableRow) inflater.inflate(R.layout.one_raw, mTableLayout, false);
	    mTableLayout.addView(row);
	
	    return row;
    }
    

    
	private LocationListener locationListener=new LocationListener() {
		@TargetApi(Build.VERSION_CODES.JELLY_BEAN_MR1)
		public void onLocationChanged(Location location) {
           /* Message.obtain(mHandler,SENSOR_SIZE + UPDATE_TIME,String.valueOf(location.getTime())).sendToTarget();
            Message.obtain(mHandler,SENSOR_SIZE + UPDATE_LONGITUDE,String.valueOf(location.getLongitude())).sendToTarget();
            Message.obtain(mHandler,SENSOR_SIZE + UPDATE_LATITUDE,String.valueOf(location.getLatitude())).sendToTarget();
            Message.obtain(mHandler,SENSOR_SIZE + UPDATE_ALTITUDE,String.valueOf(location.getAltitude())).sendToTarget();
           // Message.obtain(mHandler,SENSOR_SIZE + UPDATE_ELAPSE,String.valueOf(location.getElapsedRealtimeNanos())).sendToTarget();
            Message.obtain(mHandler,SENSOR_SIZE + UPDATE_SPEED,String.valueOf(location.getSpeed())).sendToTarget();
            //Message.obtain(mHandler,SENSOR_SIZE + UPDATE_BEAR,String.valueOf(location.getBearing())).sendToTarget();
            //Message.obtain(mHandler,SENSOR_SIZE + UPDATE_ACCURACY,String.valueOf(location.getAccuracy())).sendToTarget();*/

        }

		@Override
		public void onProviderDisabled(String arg0) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onProviderEnabled(String arg0) {
			// TODO Auto-generated method stub
			
		}

		@Override
		public void onStatusChanged(String arg0, int arg1, Bundle arg2) {
			// TODO Auto-generated method stub
			
		}
    };
  
    //状态监听
    GpsStatus.Listener GpsStatuslistener = new GpsStatus.Listener() {
        public void onGpsStatusChanged(int event) {
            switch (event) {
            case GpsStatus.GPS_EVENT_SATELLITE_STATUS:
                Log.i(TAG, "卫星状态改变");
                //获取当前状态
                GpsStatus gpsStatus=mLocationManager.getGpsStatus(null);
                //获取卫星颗数的默认最大值
                int maxSatellites = gpsStatus.getMaxSatellites();
                //创建一个迭代器保存所有卫星 
                Iterator<GpsSatellite> iters = gpsStatus.getSatellites().iterator();
                int count = 0;     
                while (iters.hasNext() && count <= maxSatellites) {     
                    GpsSatellite s = iters.next();     
                    count++;     
                }  
                Message.obtain(mHandler,SENSOR_SIZE + UPDATE_COUNT,String.valueOf(count)).sendToTarget();
                //System.out.println("搜索到："+count+"颗卫星");
                break;
            default:
            	break;
            }
        };
    };

    //状态监听
    NmeaListener Nmealistener = new GpsStatus.NmeaListener() {
		@Override
		public void onNmeaReceived(long arg0, String arg1) {
			Message.obtain(mHandler,SENSOR_SIZE + UPDATE_NMEA,String.valueOf(arg0)+ " " + arg1).sendToTarget();
           /* mLocationManager.requestLocationUpdates(LocationManager.GPS_PROVIDER, TEN_SECONDS, TEN_METERS, locationListener);
            Location location = mLocationManager.getLastKnownLocation(LocationManager.GPS_PROVIDER);
            if(location != null)
            {
            	 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_TIME,String.valueOf(location.getTime())).sendToTarget();
                 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_LONGITUDE,String.valueOf(location.getLongitude())).sendToTarget();
                 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_LATITUDE,String.valueOf(location.getLatitude())).sendToTarget();
                 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_ALTITUDE,String.valueOf(location.getAltitude())).sendToTarget();
                 //Message.obtain(mHandler,SENSOR_SIZE + UPDATE_ELAPSE,String.valueOf(location.getElapsedRealtimeNanos())).sendToTarget();
                 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_SPEED,String.valueOf(location.getSpeed())).sendToTarget();
                 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_BEAR,String.valueOf(location.getBearing())).sendToTarget();
                 Message.obtain(mHandler,SENSOR_SIZE + UPDATE_ACCURACY,String.valueOf(location.getAccuracy())).sendToTarget();            	
            }
			*/
		}
    };  

    private void addView(int base)
    {
    	for(int n = 0; n <= base + UPDATE_MAX; n++)
    	{
    		mRaw.add(getRaw());
    		mVal.add((TextView)mRaw.get(n).findViewById(R.id.row_textview_value));
    		TextView mName = (TextView) mRaw.get(n).findViewById(R.id.row_textview_name);   


    		filename.add(null);
    		if(n < base)
    		{
    		    continue;
            } 
    		switch(n -base){
		        case UPDATE_TIME:
	    			mName.setText("Time");
		            break;
		        case UPDATE_LONGITUDE:
	    			mName.setText("Longitude");
		            break;
		        case UPDATE_LATITUDE:
	    			mName.setText("Latitude");
		            break;
		        case UPDATE_ALTITUDE:
	    			mName.setText("Alititude");	    			
		            break;
		        case UPDATE_ELAPSE:
	    			mName.setText("Eclapse");	    			
		            break;
		        case UPDATE_SPEED:
	    			mName.setText("Speed");	
	    			break;
		        case UPDATE_BEAR:
	    			mName.setText("Bear");	
		            break;
		        case UPDATE_ACCURACY:
	    			mName.setText("Accuracy");	
		            break;		            
		        case UPDATE_COUNT:
	    			mName.setText("Count");	
	    			break;
		        case UPDATE_NMEA:
	    			mName.setText("Nmea");	
		            break;
		        case UPDATE_MAX:
	    			mName.setText("SysTime");	
		            break;	            
		        default:
		        	mName.setText("Unkown");
		            break;
    		}
    		filename.set(n, (String) mName.getText());
    	}  		    
    }   
    
    public class MyThread implements Runnable{
    	@Override
    	public void run() {
	    	// TODO Auto-generated method stub
	    	while (true) {
		    	try {
		    		Thread.sleep(1000);//线程暂停10秒，单位毫秒    			
		    		Message.obtain(mHandler,SENSOR_SIZE + UPDATE_TIMER,null).sendToTarget(); 
		    	} catch (InterruptedException e) {
		    	// TODO Auto-generated catch block
		    		e.printStackTrace();
	    	}
	    	}
    	}
	}
    
}
