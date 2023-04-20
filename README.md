# cAVRos
AVR C++ Framework - simple, fast, modern, type safe
 
Example:
In Register ADCSRA unset bit ADPS0, set bit ADPS1 and ADPS2. And then set bit ADEN. Leave all other bits untouched. The generatred asm code is identical. 

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
