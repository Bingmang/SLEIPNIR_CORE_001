/******************************************************************************/
/* File:    vectors.h
*
* Purpose: Provide custom interrupt service routines for Kinetis. 
*
* NOTE: This vector table is a superset table, so interrupt sources might be 
*       listed that are not available on the specific Kinetis device you are 
*       using.
*******************************************************************************/

#ifndef __VECTORS_H__
#define __VECTORS_H__


// function prototype for default_isr in vectors.c
void default_isr(void);

//void abort_isr(void);

//void hard_fault_handler_c(unsigned int * hardfault_args);

/* Interrupt Vector Table Function Pointers */
typedef void pointer(void);

extern void __startup(void);

extern unsigned long __BOOT_STACK_ADDRESS[];
extern void __iar_program_start(void);
                                        
#define VECTOR_000      (pointer*)__BOOT_STACK_ADDRESS	//          
#define VECTOR_001      __startup       // 
#define VECTOR_002      default_isr     // 
#define VECTOR_003      default_isr     // 
#define VECTOR_004      default_isr     // 
#define VECTOR_005      default_isr     // 
#define VECTOR_006      default_isr     // 
#define VECTOR_007      default_isr     //                            
#define VECTOR_008      default_isr     //                            
#define VECTOR_009      default_isr     // 
#define VECTOR_010      default_isr     // 
#define VECTOR_011      default_isr     // 
#define VECTOR_012      default_isr     // 
#define VECTOR_013      default_isr     //                           
#define VECTOR_014      default_isr     // 
#define VECTOR_015      default_isr     // 
#define VECTOR_016      default_isr     // 
#define VECTOR_017      default_isr     // 
#define VECTOR_018      default_isr     // 
#define VECTOR_019      default_isr     //
#define VECTOR_020      default_isr     // 
#define VECTOR_021      default_isr     // 
#define VECTOR_022      default_isr     // 
#define VECTOR_023      default_isr     // 
#define VECTOR_024      default_isr     // 
#define VECTOR_025      default_isr     // 
#define VECTOR_026      default_isr     // 
#define VECTOR_027      default_isr     // 
#define VECTOR_028      default_isr     // 
#define VECTOR_029      default_isr     // 
#define VECTOR_030      default_isr     // 
#define VECTOR_031      default_isr     // 
#define VECTOR_032      default_isr     // 
#define VECTOR_033      default_isr     // 
#define VECTOR_034      default_isr     //
#define VECTOR_035      default_isr     // 
#define VECTOR_036      default_isr     //
#define VECTOR_037      default_isr     //
#define VECTOR_038      default_isr     //
#define VECTOR_039      default_isr     //
#define VECTOR_040      default_isr     //
#define VECTOR_041      default_isr     //
#define VECTOR_042      default_isr     //
#define VECTOR_043      default_isr     //
#define VECTOR_044      default_isr     //
#define VECTOR_045      default_isr     //
#define VECTOR_046      default_isr     //
#define VECTOR_047      default_isr     //
#define VECTOR_048      default_isr     //
#define VECTOR_049      default_isr     //
#define VECTOR_050      default_isr     //
#define VECTOR_051      default_isr     //
#define VECTOR_052      default_isr     //
#define VECTOR_053      default_isr     //
#define VECTOR_054      default_isr     //
#define VECTOR_055      default_isr     //
#define VECTOR_056      default_isr     // 
#define VECTOR_057      default_isr     //
#define VECTOR_058      default_isr     //
#define VECTOR_059      default_isr     //
#define VECTOR_060      default_isr     //
#define VECTOR_061      default_isr     //
#define VECTOR_062      default_isr     // 
#define VECTOR_063      default_isr     //
#define VECTOR_064      default_isr     //
#define VECTOR_065      default_isr     //
#define VECTOR_066      default_isr     //
#define VECTOR_067      default_isr     //
#define VECTOR_068      default_isr     //
#define VECTOR_069      default_isr     //
#define VECTOR_070      default_isr     //
#define VECTOR_071      default_isr     //
#define VECTOR_072      default_isr     //
#define VECTOR_073      default_isr     //
#define VECTOR_074      default_isr     //
#define VECTOR_075      default_isr     // 
#define VECTOR_076      default_isr     //
#define VECTOR_077      default_isr     //
#define VECTOR_078      default_isr     //
#define VECTOR_079      default_isr     //
#define VECTOR_080      default_isr     //
#define VECTOR_081      default_isr     //
#define VECTOR_082      default_isr     //
#define VECTOR_083      default_isr     //
#define VECTOR_084      default_isr     //
#define VECTOR_085      default_isr     //
#define VECTOR_086      default_isr     //
#define VECTOR_087      default_isr     //
#define VECTOR_088      default_isr     //
#define VECTOR_089      default_isr     //
#define VECTOR_090      default_isr     //
#define VECTOR_091      default_isr     //		 
#define VECTOR_092      default_isr     //
#define VECTOR_093      default_isr     //
#define VECTOR_094      default_isr     //
#define VECTOR_095      default_isr     //
#define VECTOR_096      default_isr     //
#define VECTOR_097      default_isr     //
#define VECTOR_098      default_isr     //
#define VECTOR_099      default_isr     //
#define VECTOR_100      default_isr     //
#define VECTOR_101      default_isr     //
#define VECTOR_102      default_isr     //
#define VECTOR_103      default_isr     //
#define VECTOR_104      default_isr     //
#define VECTOR_105      default_isr     //
#define VECTOR_106      default_isr     //
#define VECTOR_107      default_isr     //
#define VECTOR_108      default_isr     //   
#define VECTOR_109      default_isr     //   
#define VECTOR_110      default_isr     //   
#define VECTOR_111      default_isr     //    
#define VECTOR_112      default_isr     //    
#define VECTOR_113      default_isr     //   
#define VECTOR_114      default_isr     //    
#define VECTOR_115      default_isr     //   
#define VECTOR_116      default_isr     //
#define VECTOR_117      default_isr     //
#define VECTOR_118      default_isr     //
#define VECTOR_119      default_isr     //
#define VECTOR_120      default_isr     // 
#define VECTOR_121      default_isr     // 
#define VECTOR_122      default_isr     // 
#define VECTOR_123      default_isr     // 
#define VECTOR_124      default_isr     // 
#define VECTOR_125      default_isr     // 
#define VECTOR_126      default_isr     // 
#define VECTOR_127      default_isr     // 
#define VECTOR_128      default_isr     // 
#define VECTOR_129      default_isr     // 
#define VECTOR_130      default_isr     // 
#define VECTOR_131      default_isr     // 
#define VECTOR_132      default_isr     // 
#define VECTOR_133      default_isr     // 
#define VECTOR_134      default_isr     // 
#define VECTOR_135      default_isr     // 
#define VECTOR_136      default_isr     // 
#define VECTOR_137      default_isr     // 
#define VECTOR_138      default_isr     // 
#define VECTOR_139      default_isr     // 
#define VECTOR_140      default_isr     // 
#define VECTOR_141      default_isr     // 
#define VECTOR_142      default_isr     // 
#define VECTOR_143      default_isr     // 
#define VECTOR_144      default_isr     // 
#define VECTOR_145      default_isr     // 
#define VECTOR_146      default_isr     // 
#define VECTOR_147      default_isr     // 
#define VECTOR_148      default_isr     // 
#define VECTOR_149      default_isr     // 
#define VECTOR_150      default_isr     // 
#define VECTOR_151      default_isr     // 
#define VECTOR_152      default_isr     // 
#define VECTOR_153      default_isr     // 
#define VECTOR_154      default_isr     // 
#define VECTOR_155      default_isr     // 
#define VECTOR_156      default_isr     // 
#define VECTOR_157      default_isr     // 
#define VECTOR_158      default_isr     // 
#define VECTOR_159      default_isr     // 
#define VECTOR_160      default_isr     // 
#define VECTOR_161      default_isr     // 
#define VECTOR_162      default_isr     // 
#define VECTOR_163      default_isr     // 
#define VECTOR_164      default_isr     // 
#define VECTOR_165      default_isr     // 
#define VECTOR_166      default_isr     // 
#define VECTOR_167      default_isr     // 
#define VECTOR_168      default_isr     // 
#define VECTOR_169      default_isr     // 
#define VECTOR_170      default_isr     // 
#define VECTOR_171      default_isr     // 
#define VECTOR_172      default_isr     // 
#define VECTOR_173      default_isr     // 
#define VECTOR_174      default_isr     // 
#define VECTOR_175      default_isr     // 
#define VECTOR_176      default_isr     // 
#define VECTOR_177      default_isr     // 
#define VECTOR_178      default_isr     // 
#define VECTOR_179      default_isr     // 
#define VECTOR_180      default_isr     // 
#define VECTOR_181      default_isr     // 
#define VECTOR_182      default_isr     // 
#define VECTOR_183      default_isr     // 
#define VECTOR_184      default_isr     // 
#define VECTOR_185      default_isr     // 
#define VECTOR_186      default_isr     // 
#define VECTOR_187      default_isr     // 
#define VECTOR_188      default_isr     // 
#define VECTOR_189      default_isr     // 
#define VECTOR_190      default_isr     // 
#define VECTOR_191      default_isr     // 
#define VECTOR_192      default_isr     // 
#define VECTOR_193      default_isr     // 
#define VECTOR_194      default_isr     // 
#define VECTOR_195      default_isr     // 
#define VECTOR_196      default_isr     // 
#define VECTOR_197      default_isr     // 
#define VECTOR_198      default_isr     // 
#define VECTOR_199      default_isr     // 
#define VECTOR_200      default_isr     // 
#define VECTOR_201      default_isr     // 
#define VECTOR_202      default_isr     // 
#define VECTOR_203      default_isr     // 
#define VECTOR_204      default_isr     // 
#define VECTOR_205      default_isr     // 
#define VECTOR_206      default_isr     // 
#define VECTOR_207      default_isr     // 
#define VECTOR_208      default_isr     // 
#define VECTOR_209      default_isr     // 
#define VECTOR_210      default_isr     // 
#define VECTOR_211      default_isr     // 
#define VECTOR_212      default_isr     // 
#define VECTOR_213      default_isr     // 
#define VECTOR_214      default_isr     // 
#define VECTOR_215      default_isr     // 
#define VECTOR_216      default_isr     // 
#define VECTOR_217      default_isr     // 
#define VECTOR_218      default_isr     // 
#define VECTOR_219      default_isr     // 
#define VECTOR_220      default_isr     // 
#define VECTOR_221      default_isr     // 
#define VECTOR_222      default_isr     // 
#define VECTOR_223      default_isr     // 
#define VECTOR_224      default_isr     // 
#define VECTOR_225      default_isr     // 
#define VECTOR_226      default_isr     // 
#define VECTOR_227      default_isr     // 
#define VECTOR_228      default_isr     // 
#define VECTOR_229      default_isr     // 
#define VECTOR_230      default_isr     // 
#define VECTOR_231      default_isr     // 
#define VECTOR_232      default_isr     // 
#define VECTOR_233      default_isr     // 
#define VECTOR_234      default_isr     // 
#define VECTOR_235      default_isr     // 
#define VECTOR_236      default_isr     // 
#define VECTOR_237      default_isr     // 
#define VECTOR_238      default_isr     // 
#define VECTOR_239      default_isr     // 
#define VECTOR_240      default_isr     // 
#define VECTOR_241      default_isr     // 
#define VECTOR_242      default_isr     // 
#define VECTOR_243      default_isr     // 
#define VECTOR_244      default_isr     // 
#define VECTOR_245      default_isr     // 
#define VECTOR_246      default_isr     // 
#define VECTOR_247      default_isr     // 
#define VECTOR_248      default_isr     // 
#define VECTOR_249      default_isr     // 
#define VECTOR_250      default_isr     // 
#define VECTOR_251      default_isr     // 
#define VECTOR_252      default_isr     // 
#define VECTOR_253      default_isr     // 
#define VECTOR_254      default_isr     // 
#define VECTOR_255      default_isr     // 
#define CONFIG_1		(pointer*)0xffffffff 
#define CONFIG_2		(pointer*)0xffffffff 
#define CONFIG_3		(pointer*)0xffffffff
#define CONFIG_4		(pointer*)0xfffffffe
/******************************************************************************/

#endif /*__VECTORS_H__*/

/* End of "vectors.h" */
