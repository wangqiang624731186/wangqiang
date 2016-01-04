package com.neusoft.ivijni;

import android.util.Log;



public class Jniadd  {

        private final String TAG = "Jniadd";
	private OnAddListener mOnAddListener;
	static {
                System.loadLibrary("ivi_jni");
	}

	public interface OnAddListener{
		void OnAdd(int num);
	}
	
	public void addListener(OnAddListener listener)
	{
		mOnAddListener = listener;
	}

	private void postEventFromNative(int num)
	{
                Log.i(TAG, "postEventFromNative ---- >");
		System.out.println("in the add post1\n");
		if(mOnAddListener != null)
		{
                        Log.i(TAG, "OnAdd , num : " + num + "; ---- >");
			System.out.println("in the add post2\n");
			mOnAddListener.OnAdd(num);
                        Log.i(TAG, "< ---- OnAdd , num : " + num);
		}
                Log.i(TAG, "< ---- postEventFromNative ");

	}
        public int nAdd(int a, int b) {
                //Log.i(TAG, "nAdd ---- > return : " + nadd(a, b));
                return nadd(a, b);
        }

	public native int nadd(int a, int b);
}
