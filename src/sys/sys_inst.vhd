	component sys is
		port (
			audio_cfg_out_SDAT       : inout std_logic                     := 'X';             -- SDAT
			audio_cfg_out_SCLK       : out   std_logic;                                        -- SCLK
			audio_cntrlr_out_BCLK    : in    std_logic                     := 'X';             -- BCLK
			audio_cntrlr_out_DACDAT  : out   std_logic;                                        -- DACDAT
			audio_cntrlr_out_DACLRCK : in    std_logic                     := 'X';             -- DACLRCK
			audio_left_in_data       : in    std_logic_vector(15 downto 0) := (others => 'X'); -- data
			audio_left_in_valid      : in    std_logic                     := 'X';             -- valid
			audio_left_in_ready      : out   std_logic;                                        -- ready
			audio_left_out_ready     : in    std_logic                     := 'X';             -- ready
			audio_left_out_data      : out   std_logic_vector(15 downto 0);                    -- data
			audio_left_out_valid     : out   std_logic;                                        -- valid
			audio_right_in_data      : in    std_logic_vector(15 downto 0) := (others => 'X'); -- data
			audio_right_in_valid     : in    std_logic                     := 'X';             -- valid
			audio_right_in_ready     : out   std_logic;                                        -- ready
			audio_right_out_ready    : in    std_logic                     := 'X';             -- ready
			audio_right_out_data     : out   std_logic_vector(15 downto 0);                    -- data
			audio_right_out_valid    : out   std_logic;                                        -- valid
			avalon_mm_in_address     : in    std_logic_vector(26 downto 0) := (others => 'X'); -- address
			avalon_mm_in_byte_enable : in    std_logic_vector(1 downto 0)  := (others => 'X'); -- byte_enable
			avalon_mm_in_read        : in    std_logic                     := 'X';             -- read
			avalon_mm_in_write       : in    std_logic                     := 'X';             -- write
			avalon_mm_in_write_data  : in    std_logic_vector(15 downto 0) := (others => 'X'); -- write_data
			avalon_mm_in_acknowledge : out   std_logic;                                        -- acknowledge
			avalon_mm_in_read_data   : out   std_logic_vector(15 downto 0);                    -- read_data
			clk_in_clk               : in    std_logic                     := 'X';             -- clk
			dmg_double_clk_clk       : out   std_logic;                                        -- clk
			pll_0_locked_export      : out   std_logic;                                        -- export
			ps2_cmd_in_data          : in    std_logic_vector(7 downto 0)  := (others => 'X'); -- data
			ps2_cmd_in_valid         : in    std_logic                     := 'X';             -- valid
			ps2_cmd_in_ready         : out   std_logic;                                        -- ready
			ps2_data_out_ready       : in    std_logic                     := 'X';             -- ready
			ps2_data_out_data        : out   std_logic_vector(7 downto 0);                     -- data
			ps2_data_out_valid       : out   std_logic;                                        -- valid
			ps2_out_CLK              : inout std_logic                     := 'X';             -- CLK
			ps2_out_DAT              : inout std_logic                     := 'X';             -- DAT
			sd_out_b_SD_cmd          : inout std_logic                     := 'X';             -- b_SD_cmd
			sd_out_b_SD_dat          : inout std_logic                     := 'X';             -- b_SD_dat
			sd_out_b_SD_dat3         : inout std_logic                     := 'X';             -- b_SD_dat3
			sd_out_o_SD_clock        : out   std_logic;                                        -- o_SD_clock
			vga_clk_clk              : out   std_logic;                                        -- clk
			vga_in_data              : in    std_logic_vector(29 downto 0) := (others => 'X'); -- data
			vga_in_startofpacket     : in    std_logic                     := 'X';             -- startofpacket
			vga_in_endofpacket       : in    std_logic                     := 'X';             -- endofpacket
			vga_in_valid             : in    std_logic                     := 'X';             -- valid
			vga_in_ready             : out   std_logic;                                        -- ready
			vga_out_CLK              : out   std_logic;                                        -- CLK
			vga_out_HS               : out   std_logic;                                        -- HS
			vga_out_VS               : out   std_logic;                                        -- VS
			vga_out_BLANK            : out   std_logic;                                        -- BLANK
			vga_out_SYNC             : out   std_logic;                                        -- SYNC
			vga_out_R                : out   std_logic_vector(7 downto 0);                     -- R
			vga_out_G                : out   std_logic_vector(7 downto 0);                     -- G
			vga_out_B                : out   std_logic_vector(7 downto 0);                     -- B
			sys_clk_clk              : out   std_logic;                                        -- clk
			sdram_clk_clk            : out   std_logic;                                        -- clk
			sdram_out_addr           : out   std_logic_vector(12 downto 0);                    -- addr
			sdram_out_ba             : out   std_logic_vector(1 downto 0);                     -- ba
			sdram_out_cas_n          : out   std_logic;                                        -- cas_n
			sdram_out_cke            : out   std_logic;                                        -- cke
			sdram_out_cs_n           : out   std_logic;                                        -- cs_n
			sdram_out_dq             : inout std_logic_vector(15 downto 0) := (others => 'X'); -- dq
			sdram_out_dqm            : out   std_logic_vector(1 downto 0);                     -- dqm
			sdram_out_ras_n          : out   std_logic;                                        -- ras_n
			sdram_out_we_n           : out   std_logic;                                        -- we_n
			hard_reset_reset         : in    std_logic                     := 'X'              -- reset
		);
	end component sys;

	u0 : component sys
		port map (
			audio_cfg_out_SDAT       => CONNECTED_TO_audio_cfg_out_SDAT,       --    audio_cfg_out.SDAT
			audio_cfg_out_SCLK       => CONNECTED_TO_audio_cfg_out_SCLK,       --                 .SCLK
			audio_cntrlr_out_BCLK    => CONNECTED_TO_audio_cntrlr_out_BCLK,    -- audio_cntrlr_out.BCLK
			audio_cntrlr_out_DACDAT  => CONNECTED_TO_audio_cntrlr_out_DACDAT,  --                 .DACDAT
			audio_cntrlr_out_DACLRCK => CONNECTED_TO_audio_cntrlr_out_DACLRCK, --                 .DACLRCK
			audio_left_in_data       => CONNECTED_TO_audio_left_in_data,       --    audio_left_in.data
			audio_left_in_valid      => CONNECTED_TO_audio_left_in_valid,      --                 .valid
			audio_left_in_ready      => CONNECTED_TO_audio_left_in_ready,      --                 .ready
			audio_left_out_ready     => CONNECTED_TO_audio_left_out_ready,     --   audio_left_out.ready
			audio_left_out_data      => CONNECTED_TO_audio_left_out_data,      --                 .data
			audio_left_out_valid     => CONNECTED_TO_audio_left_out_valid,     --                 .valid
			audio_right_in_data      => CONNECTED_TO_audio_right_in_data,      --   audio_right_in.data
			audio_right_in_valid     => CONNECTED_TO_audio_right_in_valid,     --                 .valid
			audio_right_in_ready     => CONNECTED_TO_audio_right_in_ready,     --                 .ready
			audio_right_out_ready    => CONNECTED_TO_audio_right_out_ready,    --  audio_right_out.ready
			audio_right_out_data     => CONNECTED_TO_audio_right_out_data,     --                 .data
			audio_right_out_valid    => CONNECTED_TO_audio_right_out_valid,    --                 .valid
			avalon_mm_in_address     => CONNECTED_TO_avalon_mm_in_address,     --     avalon_mm_in.address
			avalon_mm_in_byte_enable => CONNECTED_TO_avalon_mm_in_byte_enable, --                 .byte_enable
			avalon_mm_in_read        => CONNECTED_TO_avalon_mm_in_read,        --                 .read
			avalon_mm_in_write       => CONNECTED_TO_avalon_mm_in_write,       --                 .write
			avalon_mm_in_write_data  => CONNECTED_TO_avalon_mm_in_write_data,  --                 .write_data
			avalon_mm_in_acknowledge => CONNECTED_TO_avalon_mm_in_acknowledge, --                 .acknowledge
			avalon_mm_in_read_data   => CONNECTED_TO_avalon_mm_in_read_data,   --                 .read_data
			clk_in_clk               => CONNECTED_TO_clk_in_clk,               --           clk_in.clk
			dmg_double_clk_clk       => CONNECTED_TO_dmg_double_clk_clk,       --   dmg_double_clk.clk
			pll_0_locked_export      => CONNECTED_TO_pll_0_locked_export,      --     pll_0_locked.export
			ps2_cmd_in_data          => CONNECTED_TO_ps2_cmd_in_data,          --       ps2_cmd_in.data
			ps2_cmd_in_valid         => CONNECTED_TO_ps2_cmd_in_valid,         --                 .valid
			ps2_cmd_in_ready         => CONNECTED_TO_ps2_cmd_in_ready,         --                 .ready
			ps2_data_out_ready       => CONNECTED_TO_ps2_data_out_ready,       --     ps2_data_out.ready
			ps2_data_out_data        => CONNECTED_TO_ps2_data_out_data,        --                 .data
			ps2_data_out_valid       => CONNECTED_TO_ps2_data_out_valid,       --                 .valid
			ps2_out_CLK              => CONNECTED_TO_ps2_out_CLK,              --          ps2_out.CLK
			ps2_out_DAT              => CONNECTED_TO_ps2_out_DAT,              --                 .DAT
			sd_out_b_SD_cmd          => CONNECTED_TO_sd_out_b_SD_cmd,          --           sd_out.b_SD_cmd
			sd_out_b_SD_dat          => CONNECTED_TO_sd_out_b_SD_dat,          --                 .b_SD_dat
			sd_out_b_SD_dat3         => CONNECTED_TO_sd_out_b_SD_dat3,         --                 .b_SD_dat3
			sd_out_o_SD_clock        => CONNECTED_TO_sd_out_o_SD_clock,        --                 .o_SD_clock
			vga_clk_clk              => CONNECTED_TO_vga_clk_clk,              --          vga_clk.clk
			vga_in_data              => CONNECTED_TO_vga_in_data,              --           vga_in.data
			vga_in_startofpacket     => CONNECTED_TO_vga_in_startofpacket,     --                 .startofpacket
			vga_in_endofpacket       => CONNECTED_TO_vga_in_endofpacket,       --                 .endofpacket
			vga_in_valid             => CONNECTED_TO_vga_in_valid,             --                 .valid
			vga_in_ready             => CONNECTED_TO_vga_in_ready,             --                 .ready
			vga_out_CLK              => CONNECTED_TO_vga_out_CLK,              --          vga_out.CLK
			vga_out_HS               => CONNECTED_TO_vga_out_HS,               --                 .HS
			vga_out_VS               => CONNECTED_TO_vga_out_VS,               --                 .VS
			vga_out_BLANK            => CONNECTED_TO_vga_out_BLANK,            --                 .BLANK
			vga_out_SYNC             => CONNECTED_TO_vga_out_SYNC,             --                 .SYNC
			vga_out_R                => CONNECTED_TO_vga_out_R,                --                 .R
			vga_out_G                => CONNECTED_TO_vga_out_G,                --                 .G
			vga_out_B                => CONNECTED_TO_vga_out_B,                --                 .B
			sys_clk_clk              => CONNECTED_TO_sys_clk_clk,              --          sys_clk.clk
			sdram_clk_clk            => CONNECTED_TO_sdram_clk_clk,            --        sdram_clk.clk
			sdram_out_addr           => CONNECTED_TO_sdram_out_addr,           --        sdram_out.addr
			sdram_out_ba             => CONNECTED_TO_sdram_out_ba,             --                 .ba
			sdram_out_cas_n          => CONNECTED_TO_sdram_out_cas_n,          --                 .cas_n
			sdram_out_cke            => CONNECTED_TO_sdram_out_cke,            --                 .cke
			sdram_out_cs_n           => CONNECTED_TO_sdram_out_cs_n,           --                 .cs_n
			sdram_out_dq             => CONNECTED_TO_sdram_out_dq,             --                 .dq
			sdram_out_dqm            => CONNECTED_TO_sdram_out_dqm,            --                 .dqm
			sdram_out_ras_n          => CONNECTED_TO_sdram_out_ras_n,          --                 .ras_n
			sdram_out_we_n           => CONNECTED_TO_sdram_out_we_n,           --                 .we_n
			hard_reset_reset         => CONNECTED_TO_hard_reset_reset          --       hard_reset.reset
		);

