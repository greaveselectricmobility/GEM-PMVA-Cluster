#ifndef BUZZER_H
#define BUZZER_H

void Buzzer_check(Cluster_Data_t *Cluster_Data,uint32_t gem_timer);
uint8_t Buzzer_frequency(int blink_rate_interval, int blink_ctrl,uint32_t gem_timer);
void GEM_Buzzer_Module(	Cluster_Data_t *Cluster_Data, uint32_t gem_timer );
void Duty_Cycle_select(uint8_t dc);
void Buzzer_ON_OFF(uint8_t value,uint8_t dc);

#endif