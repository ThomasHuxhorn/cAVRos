# cAVRos
AVR C++ Framework - simple, fast, modern, type safe
 
Every hardware register is implemented as a type and every bit number is implemented as a strong typed enum. A lot of common mistakes while working with low level hardware access are detected at compile time.

This abstractions and type safety comes with zero cost. This means the generatoed asm code is often identical to manual bit maipulation code.
 
 
Example 1: Initalize ADC <br />
In Register ADCSRA unset bit ADPS0, set bit ADPS1 and ADPS2. And then set bit ADEN. Leave all other bits untouched. The generated asm code is identical. 

<table>
<tr><th>Before</th> <th>After</th></tr>
<tr><td>
<pre>
ADCSRA = (ADCSRA & ~_BV(ADPS0)) | _BV(ADPS1) | _BV(ADPS2);
ADCSRA |= _BV(ADEN);
</pre>
</td>

<td>    
<pre>
AD_CSRA.ADPS = ADPS2 | ADPS1;
AD_CSRA.ADEN = true;
</pre>
</td>
</tr>

<tr>
<td>
<pre>
in r24,0x6
andi r24,lo8(-8)
ori r24,lo8(6)
out 0x6,r24
sbi 0x6,7
</pre>
</td>

<td>
<pre>
in r24,0x6
andi r24,lo8(-8)
ori r24,lo8(6)
out 0x6,r24
sbi 0x6,7
</pre>
</td>
</tr>
</table>


 
Example 2: Start ADC conversion <br />
Set channel, start conversion, wailt until finish, return 16 bit value.

<table>
<tr><th>Before</th> <th>After</th></tr>
<tr><td>
<pre>
ADMUX= (ADMUX & 0xF0) | (channel & 0xF);
ADCSRA |= _BV(ADSC);
while (ADCSRA & _BV(ADSC) );
return ADC;
</pre>
</td>

<td>    
<pre>
AD_MUX.setChannel(channel);
AD_CSRA.ADSC = true;
while (AD_CSRA.ADSC);
return ADC;
</pre>
</td>
</tr>

<tr>
<td>
<pre>
        in r25,0x7
        andi r25,lo8(-16)
        andi r24,lo8(15)
        or r25,r24
        out 0x7,r25
        sbi 0x6,6
.L3:
        sbic 0x6,6
        rjmp .L3
        in r24,0x4
        in r25,0x4+1
</pre>
</td>

<td>
<pre>
        andi r24,lo8(15)
        in r25,0x7
        andi r25,lo8(-16)
        or r24,r25
        out 0x7,r24
        sbi 0x6,6
.L4:
        sbic 0x6,6
        rjmp .L4
        in r24,0x4
        in r25,0x4+1
</pre>
</td>
</tr>
</table>
