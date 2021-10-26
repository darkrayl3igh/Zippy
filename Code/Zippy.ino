float Kp = 20, Ki = 0, Kd = 0;
float error = 0, P = 0, I = 0, D = 0, PID_value = 0;
float previous_error = 0, previous_I = 0;
int sen1 = 0, sen2 = 0, sen3 = 0, sen4 = 0, sen5 = 0;
int initial_motor_speed = 100 , left_motor_speed = 0 , right_motor_speed = 0;
int X = 0; // Background
int Y = 1; // Line

void read_sensor_values(void);
void calculate_pid(void);
void motor_control(void);

void setup()
{
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(5, OUTPUT);
}

void loop()
{
  read_sensor_values();
  calculate_pid();
  motor_control();
}

void read_sensor_values()
{
  sen1 = digitalRead(A0);
  sen2 = digitalRead(A1);
  sen3 = digitalRead(A2);
  sen4 = digitalRead(A3);
  sen5 = digitalRead(A4);

  if      ((sen1 == X) && (sen2 == X) && (sen3 == X) && (sen4 == X) && (sen5 == Y)) error = 4;
  else if ((sen1 == X) && (sen2 == X) && (sen3 == X) && (sen4 == Y) && (sen5 == Y)) error = 3;
  else if ((sen1 == X) && (sen2 == X) && (sen3 == X) && (sen4 == Y) && (sen5 == X)) error = 2;
  else if ((sen1 == X) && (sen2 == X) && (sen3 == Y) && (sen4 == Y) && (sen5 == X)) error = 1;

  else if ((sen1 == X) && (sen2 == X) && (sen3 == Y) && (sen4 == X) && (sen5 == X)) error = 0;

  else if ((sen1 == X) && (sen2 == Y) && (sen3 == Y) && (sen4 == X) && (sen5 == X)) error = -1;
  else if ((sen1 == X) && (sen2 == Y) && (sen3 == X) && (sen4 == X) && (sen5 == X)) error = -2;
  else if ((sen1 == Y) && (sen2 == Y) && (sen3 == X) && (sen4 == X) && (sen5 == X)) error = -3;
  else if ((sen1 == Y) && (sen2 == X) && (sen3 == X) && (sen4 == X) && (sen5 == X)) error = -4;
  else if ((sen1 == X) && (sen2 == X) && (sen3 == X) && (sen4 == X) && (sen5 == X))
  {
    if (error == 4)
    {
      error = 5;
    }

    else if (error == -4)
    {
      error = -5;
    }
  }
}

void calculate_pid()
{
  P = error;
  I = error + previous_I;
  D = error - previous_error;

  PID_value = (Kp * P) + (Ki * I) + (Kd * D);

  previous_I = I;
  previous_error = error;
}

void motor_control()
{
  left_motor_speed = initial_motor_speed - PID_value;
  right_motor_speed = initial_motor_speed + PID_value;

  left_motor_speed = constrain(left_motor_speed, 0, 255);
  right_motor_speed = constrain(right_motor_speed, 0, 255);

  analogWrite(5, left_motor_speed);
  analogWrite(10, right_motor_speed);

  forward();
}

void forward()
{
  digitalWrite(7, HIGH);
  digitalWrite(6, LOW);
  digitalWrite(8, HIGH);
  digitalWrite(9, LOW);
}
