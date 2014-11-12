package com.eegeo.poicreation;

import android.view.View;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import com.eegeo.mobileexampleapp.MainActivity;
import com.eegeo.mobileexampleapp.R;

public class PoiCreationConfirmationView implements View.OnClickListener 
{
	protected MainActivity m_activity = null;
	protected long m_nativeCallerPointer;
	protected LinearLayout m_view = null;
	protected Button m_closeButton = null;
	protected Button m_confirmButton = null;
	
	private float m_yPosActive;
	private float m_yPosInactive;
	
	private final long m_stateChangeAnimationTimeMilliseconds = 200;
	
	public PoiCreationConfirmationView(MainActivity activity, long nativeCallerPointer)
	{
		m_activity = activity;
		m_nativeCallerPointer = nativeCallerPointer;

		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				createView();
			}
		});
	}
	
	public void destroy()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
				uiRoot.removeView(m_view);
				m_view = null;
			}
		});
	}
	
	private void createView()
	{
		final RelativeLayout uiRoot = (RelativeLayout)m_activity.findViewById(R.id.ui_container);
		m_view = (LinearLayout)m_activity.getLayoutInflater().inflate(R.layout.poi_creation_confirmation_layout, uiRoot, false);
		
		m_closeButton = (Button)m_view.findViewById(R.id.poi_creation_confirmation_close_button);
		m_closeButton.setOnClickListener(this);
		m_confirmButton = (Button)m_view.findViewById(R.id.poi_creation_confirmation_ok_button);
		m_confirmButton.setOnClickListener(this);
		
		m_yPosActive = uiRoot.getHeight() - m_activity.dipAsPx(75);
		m_yPosInactive = uiRoot.getHeight();
		
		m_view.setX(0);
		m_view.setY(m_yPosInactive);
		
		uiRoot.addView(m_view);
	}
	
	public void animateToActive()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				animateViewToY((int)m_yPosActive);
			}
		});	
	}
	
	public void animateToInactive()
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{
				animateViewToY((int)m_yPosInactive);
			}
		});	
	}
	
	protected void animateViewToY(final int yAsPx)
	{
		m_view.animate()
			.y(yAsPx)
			.setDuration(m_stateChangeAnimationTimeMilliseconds);
	}
	
	public void animateToIntermediateOnScreenState(final float onScreenState)
	{
		m_activity.runOnUiThread(new Runnable()
		{
			public void run()
			{   
				int viewXPx = (int)m_view.getX();
			    int newXPx = (int)(m_yPosInactive + (int)(((m_yPosActive - m_yPosInactive) * onScreenState) + 0.5f));
			 
			    if(viewXPx != newXPx) 
			    {
				    m_view.setY(newXPx);
			    }
			}
		});
	}

	@Override
	public void onClick(final View view) 
	{
		m_activity.runOnNativeThread(new Runnable()
		{
			public void run()
			{
				if(view == m_closeButton)
				{
					PoiCreationJniMethods.ConfirmationCancelButtonPressed(m_nativeCallerPointer);
				}
				else if(view == m_confirmButton)
				{
					PoiCreationJniMethods.ConfirmationOkButtonPressed(m_nativeCallerPointer);
				}
			}
		});
		
	}
}
