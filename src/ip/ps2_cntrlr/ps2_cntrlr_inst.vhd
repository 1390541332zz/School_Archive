	component ps2_cntrlr is
		port (
			ps2_0_reset         : in    std_logic                    := 'X';             -- reset
			ps2_0_PS2_CLK       : inout std_logic                    := 'X';             -- CLK
			ps2_0_PS2_DAT       : inout std_logic                    := 'X';             -- DAT
			ps2_0_command       : in    std_logic_vector(7 downto 0) := (others => 'X'); -- data
			ps2_0_command_valid : in    std_logic                    := 'X';             -- valid
			ps2_0_command_ready : out   std_logic;                                       -- ready
			ps2_0_data_ready    : in    std_logic                    := 'X';             -- ready
			ps2_0_data          : out   std_logic_vector(7 downto 0);                    -- data
			ps2_0_data_valid    : out   std_logic;                                       -- valid
			clk_clk             : in    std_logic                    := 'X';             -- clk
			reset_reset_n       : in    std_logic                    := 'X'              -- reset_n
		);
	end component ps2_cntrlr;

	u0 : component ps2_cntrlr
		port map (
			ps2_0_reset         => CONNECTED_TO_ps2_0_reset,         --                   ps2_0_reset.reset
			ps2_0_PS2_CLK       => CONNECTED_TO_ps2_0_PS2_CLK,       --      ps2_0_external_interface.CLK
			ps2_0_PS2_DAT       => CONNECTED_TO_ps2_0_PS2_DAT,       --                              .DAT
			ps2_0_command       => CONNECTED_TO_ps2_0_command,       -- ps2_0_avalon_ps2_command_sink.data
			ps2_0_command_valid => CONNECTED_TO_ps2_0_command_valid, --                              .valid
			ps2_0_command_ready => CONNECTED_TO_ps2_0_command_ready, --                              .ready
			ps2_0_data_ready    => CONNECTED_TO_ps2_0_data_ready,    --  ps2_0_avalon_ps2_data_source.ready
			ps2_0_data          => CONNECTED_TO_ps2_0_data,          --                              .data
			ps2_0_data_valid    => CONNECTED_TO_ps2_0_data_valid,    --                              .valid
			clk_clk             => CONNECTED_TO_clk_clk,             --                           clk.clk
			reset_reset_n       => CONNECTED_TO_reset_reset_n        --                         reset.reset_n
		);

