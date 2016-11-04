#ifndef PAL3PATCH_PATCH_COMMON_H
#define PAL3PATCH_PATCH_COMMON_H

#define GAME_WIDTH_ORG 800
#define GAME_HEIGHT_ORG 600

// all patchs
MAKE_PATCHSET(testcombat);
MAKE_PATCHSET(cdpatch);
MAKE_PATCHSET(regredirect);
MAKE_PATCHSET(disablekbdhook);
MAKE_PATCHSET(depcompatible);
MAKE_PATCHSET(setlocale);
MAKE_PATCHSET(dpiawareness);
MAKE_PATCHSET(powersave);
MAKE_PATCHSET(timerresolution);
MAKE_PATCHSET(fixmemfree);
MAKE_PATCHSET(nocpk);
MAKE_PATCHSET(showfps);
MAKE_PATCHSET(console); 

MAKE_PATCHSET(graphicspatch);
    extern int game_width, game_height;
    extern fRECT game_frect, game_frect_43, game_frect_original;
    extern double game_scalefactor;
    enum scalefactor_index_name {
        // all scalefactor should be set when stage2 is complete
        // uireplacefont will read them after creating D3D device
        
        // these 2 values is initialized by graphicspatch
        SF_IDENTITY, // equals to 1.0
        SF_GAMEFACTOR,
        
        // these values need initinialize by their own init functions
        SF_UIFACTOR,
        SF_COMBAT,
        
        // NOTE: if you want to modify this enum, pay attention to the size limit in struct uiwnd_ptag
        SCALEFACTOR_COUNT // EOF
    };
    extern double scalefactor_table[SCALEFACTOR_COUNT];
    extern double str2scalefactor(const char *str);
    
    MAKE_PATCHSET(fixfov);
    MAKE_PATCHSET(nolockablebackbuffer);
    MAKE_PATCHSET(fixreset);
    MAKE_PATCHSET(fixui);
        struct fixui_state {
            fRECT src_frect, dst_frect;
            int lr_method, tb_method;
            double len_factor;
            struct fixui_state *prev;
        };
        extern struct fixui_state *fs;

        #define ui_scalefactor (scalefactor_table[SF_UIFACTOR])
        extern void fixui_update_gamestate();
        
        enum uiwnd_rect_type { // PTR = pos tag rect
            PTR_GAMERECT,
            PTR_GAMERECT_43,
            PTR_GAMERECT_ORIGINAL,
            PTR_INHERIT,
            // NOTE: if you want to modify this enum, pay attention to the size limit in struct uiwnd_ptag
        };
        int parse_uiwnd_rect_type(const char *str);
        
        extern void fixui_pushstate(fRECT *src_frect, fRECT *dst_frect, int lr_method, int tb_method, double len_factor);
        extern void fixui_popstate();
        
        struct uiwnd_ptag {
            unsigned short scalefactor_index : 4;
            unsigned short self_srcrect_type : 2;
            unsigned short self_dstrect_type : 2;
            unsigned short self_lr_method : 2;
            unsigned short self_tb_method : 2;
            unsigned short enabled : 1;
        };
        #define PWND(addr) TOPTR(M_DWORD(addr))
        #define MAKE_PTAG(sf_idx, src_type, dst_type, lr, tb) \
            ((struct uiwnd_ptag) { \
                .scalefactor_index = (sf_idx), \
                .self_srcrect_type = (src_type), \
                .self_dstrect_type = (dst_type), \
                .self_lr_method = (lr), \
                .self_tb_method = (tb), \
                .enabled = 1, \
            })
        extern void set_uiwnd_ptag(struct UIWnd *this, struct uiwnd_ptag ptag);
        extern fRECT *get_ptag_frect(int rect_type);
        
        extern void fixui_adjust_fRECT(fRECT *out_frect, fRECT *frect);
        extern void fixui_adjust_gbUIQuad(struct gbUIQuad *out_uiquad, const struct gbUIQuad *uiquad);
        extern void fixui_adjust_RECT(RECT *out_rect, const RECT *rect);
        extern void fixui_adjust_fPOINT(fPOINT *out_fpoint, const fPOINT *fpoint);
        extern void fixui_adjust_POINT(POINT *out_point, const POINT *point);
        
        MAKE_PATCHSET(uireplacefont);
        MAKE_PATCHSET(fixloadingfrm);
        MAKE_PATCHSET(fixcombatui);
            #define cb_scalefactor (scalefactor_table[SF_COMBAT])
        MAKE_PATCHSET(fixroledialog);
        MAKE_PATCHSET(fixgameover);
    MAKE_PATCHSET(replacetexture);

#endif
