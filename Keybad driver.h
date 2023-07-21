/*
 * Keybad_driver.h
 *
 * Created: 24/09/2021 4:54:09 PM
 *  Author: kamar salah
 */ 


#ifndef KEYBAD DRIVER_H_
#define KEYBAD DRIVER_H_

#define NOTBRESSED 0xff                                    // 1111 1111 

/*function description:
intialize pin input or output and activiate internal pull up
*/
void Keybad_vinit (void);

/*function description:
cheak witch switch is compresed
*/
unsigned char Keybad_u8check_press (void);

#endif /* KEYBAD DRIVER_H_ */