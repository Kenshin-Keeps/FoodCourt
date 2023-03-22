void Yaw_y1(){
    GLfloat tx, tz;

    tx = look_x - eye_x;
    tz = look_z - eye_z;

    dx = tx*cs_angle+tz*sn_angle;
    dz = -tx*sn_angle+tz*cs_angle;

    look_x = dx + eye_x;
    look_z = dz + eye_z;

}

void Yaw_y2(){
    GLfloat tx, tz;

    tx = look_x - eye_x;
    tz = look_z - eye_z;

    dx = tx*cs_angle-tz*sn_angle;
    dz = tx*sn_angle+tz*cs_angle;

    look_x = dx + eye_x;
    look_z = dz + eye_z;
}

void Pitch_y1(){
    GLfloat ty, tz;

    ty = look_y - eye_y;
    tz = look_z - eye_z;

    dy = ty*cs_angle-tz*sn_angle;
    dz = ty*sn_angle+tz*cs_angle;

    look_y = dy + eye_y;
    look_z = dz + eye_z;
}
void Pitch_y2(){
    GLfloat ty, tz;

    ty = look_y - eye_y;
    tz = look_z - eye_z;

    dy = ty*cs_angle+tz*sn_angle;
    dz = -ty*sn_angle+tz*cs_angle;

    look_y = dy + eye_y;
    look_z = dz + eye_z;

}

void Roll_y1(){
    dx = ux*cs_angle-uy*sn_angle;
    dy = ux*sn_angle+uy*cs_angle;

    ux = dx;
    uy = dy;
}

void Roll_y2(){
    dx = ux*cs_angle+uy*sn_angle;
    dy = -ux*sn_angle+uy*cs_angle;

    ux = dx;
    uy = dy;
}

void rotation_eye_right()
{
    eye_x-=look_x;
    eye_z-=look_z;

    float r = sqrt(eye_x*eye_x + eye_z*eye_z);
    float theta_rad = atan(eye_z/eye_x);
    float conv = 180/3.1416;
    float theta_degree = theta_rad*conv;

    if(eye_x < 0 ) theta_degree +=180;

    theta_degree+=1;
    theta_rad = theta_degree/conv;

    eye_x = r*cos(theta_rad);
    eye_z = r*sin(theta_rad);

    eye_x+=look_x;
    eye_z+=look_z;

}
void rotation_eye_left()
{
    eye_x-=look_x;
    eye_z-=look_z;

    float r = sqrt(eye_x*eye_x + eye_z*eye_z);
    float theta_rad = atan(eye_z/eye_x);
    float conv = 180/3.1416;
    float theta_degree = theta_rad*conv;

    if(eye_x < 0 ) theta_degree +=180;

    theta_degree-=1;
    theta_rad = theta_degree/conv;

    eye_x = r*cos(theta_rad);
    eye_z = r*sin(theta_rad);

    eye_x+=look_x;
    eye_z+=look_z;

}

void unitZoomIn(){
    dx = eye_x-look_x;
    dy = eye_y-look_y;
    dz = eye_z-look_z;
    dxyz = sqrt(dx*dx+dy*dy+dz*dz);
    eye_x-=(dx/dxyz);
    eye_y-=(dy/dxyz);
    eye_z-=(dz/dxyz);
    look_x-=(dx/dxyz);
    look_y-=(dy/dxyz);
    look_z-=(dz/dxyz);
}

void unitZoomOut(){
    dx = eye_x-look_x;
    dy = eye_y-look_y;
    dz = eye_z-look_z;
    dxyz = sqrt(dx*dx+dy*dy+dz*dz);
    eye_x+=(dx/dxyz);
    eye_y+=(dy/dxyz);
    eye_z+=(dz/dxyz);
    look_x+=(dx/dxyz);
    look_y+=(dy/dxyz);
    look_z+=(dz/dxyz);
}
