package com.example.jochm.robocontr;

import android.content.Context;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.os.Handler;
import android.support.v7.app.AppCompatActivity;
import android.os.Bundle;
import android.util.Log;
import android.view.View;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import java.io.BufferedInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.net.Socket;
import java.net.UnknownHostException;

public class MainActivity extends AppCompatActivity {

    static String ip = "10.10.10.1";
    TextView logTextView;
    EditText ipEditText;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        /* Setting text views vars */
        logTextView = findViewById(R.id.logoMain);
        logTextView.setText("Press any button to start playing around");
        ipEditText = findViewById(R.id.ipAdd);
        ipEditText.setText(ip);


    }

    /*--------------Message picker-------------*/
    public void picker(View view){
        String str = ((Button) view).getText().toString().toLowerCase();
        ip = ipEditText.getText().toString();
        sendMessage(str);
    }


    /*--------------Server Code----------------*/
    private void sendMessage(final String msg) {
        final Integer port = 666;


        Thread thread = new Thread (new Runnable() {
            @Override
            public void run() {

                try {
                    /* Opening socket */
                    Socket s = new Socket(ip, port);
                    DataOutputStream out = new DataOutputStream(s.getOutputStream());

                    /* Cleaning stream and sending message*/
                    out.flush();
                    out.writeBytes(msg + "\r");

                    /* Close socket and stream */
                    out.close();
                    s.close();

                    System.out.println("message \"" + msg + "\" sent, the server is " + s.isConnected());
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        });

        thread.start();
        Log.d("BAR", "thread started");

        logTextView.setText("Moving " + msg);
    }
}
