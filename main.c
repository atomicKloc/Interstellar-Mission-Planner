//Interstellar Mission planner
//by Adam Kloc
//Used to plan delta V requirements (as determined though classical physics) for journeys at relitivistic speeds

#include <stdio.h>
#include <math.h>
#include <time.h>

int delay(unsigned int delay_time) {
    unsigned int start_time = (unsigned int)time(NULL);
    while (1) {
        fflush(stdout); 
        if ((unsigned int)time(NULL)-start_time>=delay_time){
            return 1;
        }
    }
}
int main() {
    printf("▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▄▄▖▗▄▄▖  ▗▄▄▖▗▄▄▄▖▗▄▄▄▖▗▖   ▗▖    ▗▄▖ ▗▄▄▖ \n  █  ▐▛▚▖▐▌  █  ▐▌   ▐▌ ▐▌▐▌     █  ▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▌ ▐▌\n  █  ▐▌ ▝▜▌  █  ▐▛▀▀▘▐▛▀▚▖ ▝▀▚▖  █  ▐▛▀▀▘▐▌   ▐▌   ▐▛▀▜▌▐▛▀▚▖\n▗▄█▄▖▐▌  ▐▌  █  ▐▙▄▄▖▐▌ ▐▌▗▄▄▞▘  █  ▐▙▄▄▖▐▙▄▄▖▐▙▄▄▖▐▌ ▐▌▐▌ ▐▌\n \n \n \n ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖ ▗▄▄▖▗▄▄▄▖ ▗▄▖ ▗▖  ▗▖                        \n ▐▛▚▞▜▌  █  ▐▌   ▐▌     █  ▐▌ ▐▌▐▛▚▖▐▌                        \n ▐▌  ▐▌  █   ▝▀▚▖ ▝▀▚▖  █  ▐▌ ▐▌▐▌ ▝▜▌                        \n ▐▌  ▐▌▗▄█▄▖▗▄▄▞▘▗▄▄▞▘▗▄█▄▖▝▚▄▞▘▐▌  ▐▌                        \n \n \n \n ▗▄▄▖ ▗▖    ▗▄▖ ▗▖  ▗▖▗▖  ▗▖▗▄▄▄▖▗▄▄▖                         \n ▐▌ ▐▌▐▌   ▐▌ ▐▌▐▛▚▖▐▌▐▛▚▖▐▌▐▌   ▐▌ ▐▌                        \n ▐▛▀▘ ▐▌   ▐▛▀▜▌▐▌ ▝▜▌▐▌ ▝▜▌▐▛▀▀▘▐▛▀▚▖                        \n ▐▌   ▐▙▄▄▖▐▌ ▐▌▐▌  ▐▌▐▌  ▐▌▐▙▄▄▖▐▌ ▐▌                        \n \n \n \n");
    // Units
    double year = 31556952; // 1 year in seconds
    double light_speed = 299792458; // speed of light in meters per second
    double lightyear = year*light_speed; // 1 lightyear in meters
    printf("1 lightyear is valued as %lf meters in this simulation\n", lightyear);
    // Targets
    double target_mission_length = 1; // desired length of mission in years
    double desired_distance = 4.344*lightyear; // how far you want to travel in meters
    // Simulation Variables
    double timestep_length = 1; // length of timestep in seconds
    unsigned int timesteps_passed = 0;
    double time_passed = 0;
    double ETA = 1;
    // Ship Variables
    double ship_acceleration = 9.806; // the acceleration of your ship
    double ship_velocity = 0; // velocity of your ship
    double ship_position = 0; // ship position in meters
    double ship_delta_v = 100000; // delta v of your ship
    double ship_second = 1; // how much time passes on this ship, given 1 second passes for a stationary observer
    double ship_time = 0; // time elapsed on ship
    double ship_ETA = 1; // expected time of arrival with respect to the cargo
    double delta_v_used = 0; // amount of delta V used from the start of the mission
    double ship_experation = 0; // how long it takes for the cargo to expire

    printf("Enter target distance in light years : ");
    scanf("%lf",&desired_distance);
    desired_distance *= lightyear;
    printf("Enter target mission duration in years : ");
    scanf("%lf",&target_mission_length);
    printf("Enter the expiry time for the cargo in years : ");
    scanf("%lf",&ship_experation);
    printf("Enter the available delta v in m/s : ");
    scanf("%lf",&ship_delta_v);
    printf("I hope this hurts");
    fflush(stdout);
    delay(1);
    printf("\rsimulating...    \n");
    while(timesteps_passed < (unsigned int)(target_mission_length*year/timestep_length)) { //u=(c^2)*(v1+v2)/(v1*v2+c^2)
        timesteps_passed += 1;
        time_passed += timestep_length;
        ship_second = sqrt(1-pow(ship_velocity/light_speed,(double)2));
        //ship_velocity += ship_acceleration*timestep_length;
        
        ship_velocity = light_speed*light_speed*(ship_velocity+ship_second*ship_acceleration*timestep_length)
        /(ship_second*ship_velocity*ship_acceleration*timestep_length+light_speed*light_speed);
        ship_position += ship_velocity*timestep_length;
        ship_time += ship_second*timestep_length;
        ETA = 2*(time_passed+(desired_distance/2-ship_position)/ship_velocity);
        ship_ETA = 2*(ship_time+ship_second*((desired_distance/2-ship_position)/ship_velocity));
        delta_v_used += ship_acceleration*timestep_length*ship_second;
        if (ETA <= target_mission_length*year && ship_ETA <= ship_experation*year) {
            break;
        }
        if (delta_v_used > ship_delta_v/2) {
            break;
        }
    }
    printf("Mission took %lf years\n", ETA/year);
    printf("Ship experienced %lf years\n", ship_ETA/year);
    printf("Ship reached a maximum velocity of %lf c\n", ship_velocity/light_speed);
    printf("Ship used %lf m/s of delta v\n", 2*delta_v_used);
}