	component audio_cntrlr is
		port (
			audio_0_reset                        : in  std_logic                     := 'X';             -- reset
			audio_0_AUD_BCLK                     : in  std_logic                     := 'X';             -- BCLK
			audio_0_AUD_DACDAT                   : out std_logic;                                        -- DACDAT
			audio_0_AUD_DACLRCK                  : in  std_logic                     := 'X';             -- DACLRCK
			audio_0_from_adc_left_channel_ready  : in  std_logic                     := 'X';             -- ready
			audio_0_from_adc_left_channel_data   : out std_logic_vector(15 downto 0);                    -- data
			audio_0_from_adc_left_channel_valid  : out std_logic;                                        -- valid
			audio_0_from_adc_right_channel_ready : in  std_logic                     := 'X';             -- ready
			audio_0_from_adc_right_channel_data  : out std_logic_vector(15 downto 0);                    -- data
			audio_0_from_adc_right_channel_valid : out std_logic;                                        -- valid
			audio_0_to_dac_left_channel_data     : in  std_logic_vector(15 downto 0) := (others => 'X'); -- data
			audio_0_to_dac_left_channel_valid    : in  std_logic                     := 'X';             -- valid
			audio_0_to_dac_left_channel_ready    : out std_logic;                                        -- ready
			audio_0_to_dac_right_channel_data    : in  std_logic_vector(15 downto 0) := (others => 'X'); -- data
			audio_0_to_dac_right_channel_valid   : in  std_logic                     := 'X';             -- valid
			audio_0_to_dac_right_channel_ready   : out std_logic;                                        -- ready
			clk_clk                              : in  std_logic                     := 'X';             -- clk
			reset_reset_n                        : in  std_logic                     := 'X'              -- reset_n
		);
	end component audio_cntrlr;

	u0 : component audio_cntrlr
		port map (
			audio_0_reset                        => CONNECTED_TO_audio_0_reset,                        --                       audio_0_reset.reset
			audio_0_AUD_BCLK                     => CONNECTED_TO_audio_0_AUD_BCLK,                     --          audio_0_external_interface.BCLK
			audio_0_AUD_DACDAT                   => CONNECTED_TO_audio_0_AUD_DACDAT,                   --                                    .DACDAT
			audio_0_AUD_DACLRCK                  => CONNECTED_TO_audio_0_AUD_DACLRCK,                  --                                    .DACLRCK
			audio_0_from_adc_left_channel_ready  => CONNECTED_TO_audio_0_from_adc_left_channel_ready,  --  audio_0_avalon_left_channel_source.ready
			audio_0_from_adc_left_channel_data   => CONNECTED_TO_audio_0_from_adc_left_channel_data,   --                                    .data
			audio_0_from_adc_left_channel_valid  => CONNECTED_TO_audio_0_from_adc_left_channel_valid,  --                                    .valid
			audio_0_from_adc_right_channel_ready => CONNECTED_TO_audio_0_from_adc_right_channel_ready, -- audio_0_avalon_right_channel_source.ready
			audio_0_from_adc_right_channel_data  => CONNECTED_TO_audio_0_from_adc_right_channel_data,  --                                    .data
			audio_0_from_adc_right_channel_valid => CONNECTED_TO_audio_0_from_adc_right_channel_valid, --                                    .valid
			audio_0_to_dac_left_channel_data     => CONNECTED_TO_audio_0_to_dac_left_channel_data,     --    audio_0_avalon_left_channel_sink.data
			audio_0_to_dac_left_channel_valid    => CONNECTED_TO_audio_0_to_dac_left_channel_valid,    --                                    .valid
			audio_0_to_dac_left_channel_ready    => CONNECTED_TO_audio_0_to_dac_left_channel_ready,    --                                    .ready
			audio_0_to_dac_right_channel_data    => CONNECTED_TO_audio_0_to_dac_right_channel_data,    --   audio_0_avalon_right_channel_sink.data
			audio_0_to_dac_right_channel_valid   => CONNECTED_TO_audio_0_to_dac_right_channel_valid,   --                                    .valid
			audio_0_to_dac_right_channel_ready   => CONNECTED_TO_audio_0_to_dac_right_channel_ready,   --                                    .ready
			clk_clk                              => CONNECTED_TO_clk_clk,                              --                                 clk.clk
			reset_reset_n                        => CONNECTED_TO_reset_reset_n                         --                               reset.reset_n
		);

