	component qsystop is
		port (
			clk_clk         : in  std_logic                    := 'X';             -- clk
			reset_reset_n   : in  std_logic                    := 'X';             -- reset_n
			ledout_export   : out std_logic_vector(7 downto 0);                    -- export
			switchin_export : in  std_logic_vector(7 downto 0) := (others => 'X')  -- export
		);
	end component qsystop;

	u0 : component qsystop
		port map (
			clk_clk         => CONNECTED_TO_clk_clk,         --      clk.clk
			reset_reset_n   => CONNECTED_TO_reset_reset_n,   --    reset.reset_n
			ledout_export   => CONNECTED_TO_ledout_export,   --   ledout.export
			switchin_export => CONNECTED_TO_switchin_export  -- switchin.export
		);

